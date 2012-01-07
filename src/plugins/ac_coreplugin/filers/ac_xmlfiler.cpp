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
#include <ac_point.h>

#include <mi_imodelitem.h>

#include <QApplication>
#include <QClipboard>

#include <QStringList>
#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

static const QMap<int, QString> &elementMap()
{
    static QMap<int, QString> map;
    if (map.isEmpty()) {
        map.insert(Ac::ScoreItem, "Score");
        map.insert(Ac::TrackItem, "Track");
        map.insert(Ac::NoteItem, "Note");
        map.insert(Ac::PitchCurveItem, "PitchCurve");
        map.insert(Ac::ControlCurveItem, "ControlCurve");
        map.insert(Ac::GridSettingsItem, "GridSettings");
        map.insert(Ac::TimeGridLineItem, "TimeGridLine");
        map.insert(Ac::PitchGridLineItem, "PitchGridLine");
        map.insert(Ac::ControlGridLineItem, "ControlGridLine");
        map.insert(Ac::ViewSettingsItem, "ViewSettings");
        map.insert(Ac::ProjectSettingsItem, "ProjectSettings");
    }
    return map;
}

static const QMap<int, QString> &attributeMap()
{
    static QMap<int, QString> map;
    if (map.isEmpty()) {
        map.insert(Mi::NameRole, "name");
        map.insert(Ac::PointsRole, "points");
        map.insert(Ac::ControlIdRole, "controlId");
        map.insert(Ac::LocationRole, "location");
        map.insert(Ac::LabelRole, "label");
        map.insert(Ac::PriorityRole, "priority");
        map.insert(Ac::InstrumentRole, "instrument");
        map.insert(Ac::LengthRole, "length");
        map.insert(Ac::VolumeRole, "volume");
        map.insert(Ac::ColorRole, "color");
        map.insert(Ac::VisibilityRole, "visible");
        map.insert(Ac::RecordingRole, "recording");
        map.insert(Ac::TimePositionRole, "timePosition");
        map.insert(Ac::PitchPositionRole, "pitchPosition");
        map.insert(Ac::ControlPositionRole, "controlPosition");
        map.insert(Ac::TimeScaleRole, "timeScale");
        map.insert(Ac::PitchScaleRole, "pitchScale");
        map.insert(Ac::ControlScaleRole, "controlScale");
        map.insert(Ac::OutputDirectoryRole, "outputDirectory");
        map.insert(Ac::InstrumentDirectoryRole, "instrumentDirectory");
        map.insert(Ac::SampleRateRole, "sampleRate");
        map.insert(Ac::ControlRateRole, "controlRate");
    }
    return map;
}

static QString elementName(int type)
{
    return elementMap().value(type);
}

static QString elementName(IModelItem *item)
{
    if (Mi::ListItem == item->type())
        return elementName(item->data(Mi::ListTypeRole).toInt()) + "List";
    return elementName(item->type());
}

static int elementType(const QString &name)
{
    return elementMap().key(name, Mi::UnknownItem);
}

static QString attributeName(int role)
{
    return attributeMap().value(role);
}

static int attributeRole(const QString &name)
{
    return attributeMap().key(name, Mi::InvalidRole);
}

static bool nextStartElement(QXmlStreamReader &reader)
{
    int tokenType = QXmlStreamReader::NoToken;
    while (tokenType != QXmlStreamReader::StartElement) {
        tokenType = reader.readNext();
        if (tokenType == QXmlStreamReader::Invalid)
            continue;
        if (reader.atEnd())
            return false;
    }
    return true;
}

static QXmlStreamReader::TokenType nextElement(QXmlStreamReader &reader)
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

static bool readItem(IModelItem *item, QXmlStreamReader &reader)
{
    IObjectFactory *factory = IObjectFactory::instance();

    QString elementName = reader.name().toString();
    if (elementName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << ": Empty element name";
        return false;
    }
    if (elementName.endsWith("List")) {
        QString listElementName = elementName;
        listElementName.chop(4);
        int itemType = elementType(listElementName);
        while (nextElement(reader) == QXmlStreamReader::StartElement) {
            IModelItem *newItem = factory->create(itemType);
            newItem->setParentModelItem(item);
            if (!readItem(newItem, reader)) {
                qWarning() << Q_FUNC_INFO << ": failed to read list item in" << elementName;
                return false;
            }
        }
    } else {
        QXmlStreamAttributes attributes = reader.attributes();
        foreach (const QXmlStreamAttribute &attribute, attributes) {
            QString roleString = attribute.name().toString();
            int role = attributeRole(roleString);
            if (Mi::InvalidRole == role) {
                qWarning() << Q_FUNC_INFO << ": Invalid attribute role in" << elementName;
                return false;
            }
            if (!item->setData(attribute.value().toString(), role)) {
                qWarning() << Q_FUNC_INFO << ": Set data failed in" << elementName << "at" << attribute.value().toString();
                return false;
            }
        }
        if (elementName.endsWith("Curve")) {
            PointList points;
            while (nextElement(reader) == QXmlStreamReader::StartElement) {
                Point point;
                QXmlStreamAttributes attributes = reader.attributes();
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
                nextElement(reader);
            }
            if (!item->setData(QVariant::fromValue(points), Ac::PointsRole)) {
                qWarning() << Q_FUNC_INFO << ": Set data failed in" << elementName << "at point list";
                return false;
            }
        } else {
            while (nextElement(reader) == QXmlStreamReader::StartElement) {
                QString subElementName = reader.name().toString();
                IModelItem *subItem = 0;
                if (subElementName.endsWith("List")) {
                    QString subElementListName = subElementName;
                    subElementListName.chop(4);
                    subItem = item->findModelItemList(elementType(subElementListName));
                } else
                    subItem = item->findModelItem(elementType(subElementName));
                if (!readItem(subItem, reader)) {
                    qWarning() << Q_FUNC_INFO << ": Sub-item read failed in" << elementName << "at" << subElementName;
                    return false;
                }
            }
        }
    }
    QString endElementName = reader.name().toString();
    if (endElementName != elementName)
        qWarning() << Q_FUNC_INFO << ": Mismatched element start and end tags (" << elementName << "-->" << endElementName << ")";
    return true;
}

static void writePoints(const PointList &points, QXmlStreamWriter &writer)
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

static void writeItemData(IModelItem *item, int roleIndex, QXmlStreamWriter &writer)
{
    int role = item->persistentRoleAt(roleIndex);
    QVariant data = item->data(role);
    if (Ac::PointsRole == role)
        writePoints(data.value<PointList>(), writer);
    else {
        QString dataString = data.toString();
        if (!dataString.isEmpty())
            writer.writeAttribute(attributeName(role), dataString);
    }
}

static bool writeItem(IModelItem *item, QXmlStreamWriter &writer)
{
    if (Mi::ListItem == item->type() && 0 == item->modelItemCount())
        return true;
    if (Ac::PitchCurveItem == item->type() && item->data(Ac::PointsRole).value<PointList>().isEmpty())
        return true;
    writer.writeStartElement(elementName(item));
    int roleCount = item->persistentRoleCount();
    for (int i = 0;  i < roleCount;  ++i)
        writeItemData(item, i, writer);
    int itemCount = item->modelItemCount();
    for (int i = 0;  i < itemCount;  ++i)
        if (!writeItem(item->modelItemAt(i), writer))
            return false;
    writer.writeEndElement();
    return true;
}

class XmlFileReaderPrivate : public FileFilerPrivate
{
public:
    QXmlStreamReader xml;

    XmlFileReaderPrivate(XmlFileReader *q)
        :   FileFilerPrivate(q)
        ,   xml(&file)
    {}

    QIODevice::OpenMode openMode() const
    {
        return QIODevice::Text | QIODevice::ReadOnly;
    }

    bool openFile()
    {
        if (file.isOpen())
            return true;
        if (FileFilerPrivate::openFile()) {
            xml.setDevice(&file);
            return nextStartElement(xml);
        }
        return false;
    }

    QXmlStreamReader &reader()
    {
        return xml;
    }
};

XmlFileReader::XmlFileReader(QObject *parent)
    :   FileFiler(*(new XmlFileReaderPrivate(this)), parent)
{}

int XmlFileReader::nextItemType()
{
    Q_D(XmlFileReader);
    QXmlStreamReader &reader = d->reader();
    if (!nextStartElement(reader))
        return Mi::UnknownItem;
    const QString elementName = reader.name().toString();
    return elementType(elementName);
}

bool XmlFileReader::read(IModelItem *item)
{
    Q_D(XmlFileReader);
    if (!item || !d->openFile())
        return false;
    return readItem(item, d->reader());
}

class XmlFileWriterPrivate : public FileFilerPrivate
{
public:
    QXmlStreamWriter xml;

    XmlFileWriterPrivate(XmlFileWriter *q)
        :   FileFilerPrivate(q)
        ,   xml(&file)
    {
        xml.setAutoFormatting(true);
    }

    QIODevice::OpenMode openMode() const
    {
        return QIODevice::Text | QIODevice::WriteOnly;
    }

    QXmlStreamWriter &writer()
    {
        return xml;
    }
};

XmlFileWriter::XmlFileWriter(QObject *parent)
    :   FileFiler(*(new XmlFileWriterPrivate(this)), parent)
{}

XmlFileWriter::~XmlFileWriter()
{
    Q_D(XmlFileWriter);
    d->file.write("\n");
}

bool XmlFileWriter::write(IModelItem *item)
{
    Q_D(XmlFileWriter);
    if (!item || !d->openFile())
        return false;
    return writeItem(item, d->writer());
}

class XmlCopyReaderPrivate : public CopyFilerPrivate
{
public:
    QXmlStreamReader *xml;

    XmlCopyReaderPrivate(XmlCopyReader *q)
        :   CopyFilerPrivate(q)
        ,   xml(0)
    {
        data = QString("<clipboard>") + QApplication::clipboard()->text() + "</clipboard>";
        xml = new QXmlStreamReader(data);
    }

    ~XmlCopyReaderPrivate()
    {
        delete xml;
    }

    QXmlStreamReader &reader()
    {
        return *xml;
    }
};

XmlCopyReader::XmlCopyReader(QObject *parent)
    :   CopyFiler(*(new XmlCopyReaderPrivate(this)), parent)
{
    Q_D(XmlCopyReader);

    // First start element is <clipboard>
    nextStartElement(d->reader());
}

int XmlCopyReader::nextItemType()
{
    Q_D(XmlCopyReader);
    QXmlStreamReader &reader = d->reader();
    if (!nextStartElement(reader))
        return Mi::UnknownItem;
    const QString elementName = reader.name().toString();
    return elementType(elementName);
}

bool XmlCopyReader::read(IModelItem *item)
{
    Q_D(XmlCopyReader);
    if (!item)
        return false;
    return readItem(item, d->reader());
}

class XmlCopyWriterPrivate : public CopyFilerPrivate
{
public:
    QXmlStreamWriter xml;

    XmlCopyWriterPrivate(XmlCopyWriter *q)
        :   CopyFilerPrivate(q)
        ,   xml(&data)
    {
        xml.setAutoFormatting(true);
    }

    QXmlStreamWriter &writer()
    {
        return xml;
    }
};

XmlCopyWriter::XmlCopyWriter(QObject *parent)
    :   CopyFiler(*(new XmlCopyWriterPrivate(this)), parent)
{}

XmlCopyWriter::~XmlCopyWriter()
{
    Q_D(XmlCopyWriter);
    d->data.append("/n");
}

bool XmlCopyWriter::write(IModelItem *item)
{
    Q_D(XmlCopyWriter);
    if (!item)
        return false;
    bool ret = writeItem(item, d->writer());
    return ret;
}
