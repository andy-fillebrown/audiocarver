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

#include <ac_ifactory.h>
#include <ac_imodelitem.h>
#include <ac_point.h>

#include <QStringList>
#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

static QMap<int, QString> elementMap;
static QMap<int, QString> attributeMap;

static void initMaps()
{
    if (!elementMap.isEmpty())
        return;

    elementMap.insert(Ac::ScoreItem, "Score");
    elementMap.insert(Ac::TrackItem, "Track");
    elementMap.insert(Ac::NoteItem, "Note");
    elementMap.insert(Ac::PitchCurveItem, "PitchCurve");
    elementMap.insert(Ac::ControlCurveItem, "ControlCurve");
    elementMap.insert(Ac::GridSettingsItem, "GridSettings");
    elementMap.insert(Ac::TimeGridLineItem, "TimeGridLine");
    elementMap.insert(Ac::PitchGridLineItem, "PitchGridLine");
    elementMap.insert(Ac::ControlGridLineItem, "ControlGridLine");
    elementMap.insert(Ac::ViewSettingsItem, "ViewSettings");

    attributeMap.insert(Ac::NameRole, "name");
    attributeMap.insert(Ac::PointsRole, "points");
    attributeMap.insert(Ac::ControlIdRole, "controlId");
    attributeMap.insert(Ac::LocationRole, "location");
    attributeMap.insert(Ac::LabelRole, "label");
    attributeMap.insert(Ac::PriorityRole, "priority");
    attributeMap.insert(Ac::InstrumentRole, "instrument");
    attributeMap.insert(Ac::LengthRole, "length");
    attributeMap.insert(Ac::VolumeRole, "volume");
    attributeMap.insert(Ac::ColorRole, "color");
    attributeMap.insert(Ac::VisibilityRole, "visibility");
    attributeMap.insert(Ac::TimePositionRole, "timePosition");
    attributeMap.insert(Ac::PitchPositionRole, "pitchPosition");
    attributeMap.insert(Ac::ControlPositionRole, "controlPosition");
    attributeMap.insert(Ac::TimeScaleRole, "timeScale");
    attributeMap.insert(Ac::PitchScaleRole, "pitchScale");
    attributeMap.insert(Ac::ControlScaleRole, "controlScale");
}

static QString elementName(int type)
{
    return elementMap.value(type);
}

static QString elementName(IModelItem *item)
{
    if (item->type() == Ac::ListItem)
        return elementName(item->data(Ac::ListTypeRole).toInt()) + "List";
    return elementName(item->type());
}

static int elementType(const QString &name)
{
    return elementMap.key(name, Ac::UnknownItem);
}

static QString attributeName(int role)
{
    return attributeMap.value(role);
}

static int attributeRole(const QString &name)
{
    return attributeMap.key(name, Ac::InvalidRole);
}

class XmlFileReaderPrivate : public FileReaderPrivate
{
public:
    QXmlStreamReader reader;

    XmlFileReaderPrivate(XmlFileReader *q)
        :   FileReaderPrivate(q)
        ,   reader(&file)
    {
        initMaps();
    }

    QIODevice::OpenMode openMode() const
    {
        return QIODevice::Text | QIODevice::ReadOnly;
    }

    bool openFile()
    {
        if (file.isOpen())
            return true;
        return FileReaderPrivate::openFile() && nextStartElement();
    }

    bool nextStartElement()
    {
        int tokenType = QXmlStreamReader::NoToken;
        while (tokenType != QXmlStreamReader::StartElement) {
            tokenType = reader.readNext();
            if (reader.atEnd())
                return false;
        }
        return true;
    }

    QXmlStreamReader::TokenType nextElement()
    {
        QXmlStreamReader::TokenType tokenType = QXmlStreamReader::NoToken;
        while (tokenType != QXmlStreamReader::StartElement
               && tokenType != QXmlStreamReader::EndElement) {
            tokenType = reader.readNext();
            if (reader.atEnd())
                return QXmlStreamReader::NoToken;
        }
        return tokenType;
    }
};

XmlFileReader::XmlFileReader()
    :   FileReader(*(new XmlFileReaderPrivate(this)))
{}

bool XmlFileReader::read(IModelItem *item)
{
    Q_D(XmlFileReader);
    if (!item || !d->openFile())
        return false;
    QString elementName = d->reader.name().toString();
    if (elementName.isEmpty()) {
        qWarning() << "XmlFileReader: Empty element name";
        return false;
    }
    if (elementName.endsWith("List")) {
        QString listElementName = elementName;
        listElementName.chop(4);
        int itemType = elementType(listElementName);
        while (d->nextElement() == QXmlStreamReader::StartElement) {
            IModelItem *newItem = IObjectFactory::instance()->create(itemType);
            newItem->setParentModelItem(item);
            if (!read(newItem)) {
                qWarning() << "XmlFileReader: failed to read list item in" << elementName;
                return false;
            }
        }
    } else {
        QXmlStreamAttributes attributes = d->reader.attributes();
        foreach (const QXmlStreamAttribute &attribute, attributes) {
            QString roleString = attribute.name().toString();
            int role = attributeRole(roleString);
            if (Ac::InvalidRole == role) {
                qWarning() << "XmlFileReader: Invalid attribute role in" << elementName;
                return false;
            }
            if (!item->setData(attribute.value().toString(), role)) {
                qWarning() << "XmlFileReader: Set data failed in" << elementName << "at" << attribute.value().toString();
                return false;
            }
        }
        if (elementName.endsWith("Curve")) {
            PointList points;
            while (d->nextElement() == QXmlStreamReader::StartElement) {
                Point point;
                QXmlStreamAttributes attributes = d->reader.attributes();
                foreach (const QXmlStreamAttribute &attribute, attributes) {
                    const QString &data = attribute.value().toString();
                    if ("position" == attribute.name()) {
                        QStringList coords = data.split(' ');
                        point.pos.setX(coords.at(0).toDouble());
                        point.pos.setY(coords.at(1).toDouble());
                    } else if ("curve" == attribute.name() && "bezier" == data)
                        point.curveType = Ac::BezierCurve;
                }
                points.append(point);
                d->nextElement();
            }
            if (!item->setData(QVariant::fromValue(points), Ac::PointsRole)) {
                qWarning() << "XmlFileReader: Set data failed in" << elementName << "at point list";
                return false;
            }
        } else {
            while (d->nextElement() == QXmlStreamReader::StartElement) {
                QString subElementName = d->reader.name().toString();
                IModelItem *subItem = 0;
                if (subElementName.endsWith("List")) {
                    QString subElementListName = subElementName;
                    subElementListName.chop(4);
                    subItem = item->findModelItemList(elementType(subElementListName));
                } else
                    subItem = item->findModelItem(elementType(subElementName));
                if (!read(subItem)) {
                    qWarning() << "XmlFileReader: Sub-item read failed in" << elementName << "at" << subElementName;
                    return false;
                }
            }
        }
    }
    QString endElementName = d->reader.name().toString();
    if (endElementName != elementName)
        qWarning() << "XmlFileReader: Mismatched element start and end tags (" << elementName << "-->" << endElementName << ")";
    return true;
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
        initMaps();
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
    if (!d->openFile())
        return false;
    d->writer.writeStartElement(elementName(item));
    int roleCount = item->persistentRoleCount();
    for (int i = 0;  i < roleCount;  ++i)
        d->writeItemData(item, i);
    int itemCount = item->modelItemCount();
    for (int i = 0;  i < itemCount;  ++i)
        if (!write(item->modelItemAt(i)))
            return false;
    d->writer.writeEndElement();
    return QFile::NoError == d->file.error();
}
