/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
**
** Contact: Andy Fillebrown (andy.fillebrown@gmail.com)
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file.  Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#include "ac_xmlfiler.h"

#include <ac_imodelitem.h>

#include <ac_point.h>

#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

static QString elementName(int type)
{
    switch (type) {
    case Ac::ScoreItem:
        return "Score";
    case Ac::TrackItem:
        return "Track";
    case Ac::NoteItem:
        return "Note";
    case Ac::PitchCurveItem:
        return "PitchCurve";
    case Ac::ControlCurveItem:
        return "ControlCurve";
    case Ac::GridSettingsItem:
        return "GridSettings";
    case Ac::TimeGridLineItem:
        return "TimeGridLine";
    case Ac::PitchGridLineItem:
        return "PitchGridLine";
    case Ac::ControlGridLineItem:
        return "ControlGridLine";
    case Ac::ViewSettingsItem:
        return "ViewSettings";
    default:
        return QString();
    }
}

static QString elementName(IModelItem *item)
{
    if (item->type() == Ac::ListItem)
        return elementName(item->data(Ac::ListTypeRole).toInt()) + "List";
    return elementName(item->type());
}

static QString attributeName(int role)
{
    switch (role) {
    case Ac::NameRole:
        return "name";
    case Ac::PointsRole:
        return "points";
    case Ac::ControlIdRole:
        return "controlId";
    case Ac::LocationRole:
        return "location";
    case Ac::LabelRole:
        return "label";
    case Ac::PriorityRole:
        return "priority";
    case Ac::InstrumentRole:
        return "instrument";
    case Ac::LengthRole:
        return "length";
    case Ac::VolumeRole:
        return "volume";
    case Ac::ColorRole:
        return "color";
    case Ac::VisibilityRole:
        return "visibility";
    case Ac::TimePositionRole:
        return "timePosition";
    case Ac::PitchPositionRole:
        return "pitchPosition";
    case Ac::ControlPositionRole:
        return "controlPosition";
    case Ac::TimeScaleRole:
        return "timeScale";
    case Ac::PitchScaleRole:
        return "pitchScale";
    case Ac::ControlScaleRole:
        return "controlScale";
    default:
        return QString();
    }
}

class XmlFileReaderPrivate : public FileReaderPrivate
{
public:
    XmlFileReaderPrivate(XmlFileReader *q)
        :   FileReaderPrivate(q)
    {}

    QIODevice::OpenMode openMode() const
    {
        return QIODevice::Text | QIODevice::ReadOnly;
    }
};

XmlFileReader::XmlFileReader()
    :   FileReader(*(new XmlFileReaderPrivate(this)))
{}

bool XmlFileReader::read(IModelItem *item)
{
    Q_UNUSED(item);
    return false;
}

class XmlFileWriterPrivate : public FileWriterPrivate
{
public:
    QXmlStreamWriter writer;

    XmlFileWriterPrivate(XmlFileWriter *q)
        :   FileWriterPrivate(q)
        ,   writer(&file)
    {
        writer.setAutoFormatting(true);
    }

    QIODevice::OpenMode openMode() const
    {
        return QIODevice::Text | QIODevice::WriteOnly;
    }

    void writeItemData(IModelItem *item, int roleIndex)
    {
        int role = item->persistentRoleAt(roleIndex);
        QVariant data = item->data(role);
        if (Ac::PointsRole == role)
            writePoints(data.value<PointList>());
        else {
            QString dataString = data.toString();
            if (!dataString.isEmpty())
                writer.writeAttribute(attributeName(role), dataString);
        }
    }

    void writePoints(const PointList &points)
    {
        if (points.isEmpty())
            return;
        foreach (const Point &pt, points) {
            writer.writeStartElement("Point");
            const QPointF &pos = pt.pos;
            writer.writeAttribute("position", QString("%1 %2").arg(pos.x()).arg(pos.y()));
            if (Ac::BezierCurve == pt.curveType)
                writer.writeAttribute("curve", "bezier");
            writer.writeEndElement();
        }
    }
};

XmlFileWriter::XmlFileWriter()
    :   FileWriter(*(new XmlFileWriterPrivate(this)))
{}

bool XmlFileWriter::write(IModelItem *item)
{
    Q_D(XmlFileWriter);
    if (!item)
        return false;
    if (Ac::ListItem == item->type() && 0 == item->modelItemCount())
        return true;
    if (Ac::PitchCurveItem == item->type() && item->data(Ac::PointsRole).value<PointList>().isEmpty())
        return true;
    d->openFile();
    d->writer.writeStartElement(elementName(item));
    int roleCount = item->persistentRoleCount();
    for (int i = 0;  i < roleCount;  ++i)
        d->writeItemData(item, i);
    int itemCount = item->modelItemCount();
    for (int i = 0;  i < itemCount;  ++i)
        write(item->modelItemAt(i));
    d->writer.writeEndElement();
    return QFile::NoError == d->file.error();
}
