/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_core_xmlreader.h"

#include <mi_idatabase.h>
#include <mi_idataobjectfactory.h>
#include <mi_imodeldata.h>
#include <mi_imodelitem.h>
#include <mi_imodellist.h>

#include <ac_core_point.h>

#include <QStringList>
#include <QXmlStreamReader>

static int elementType(const QString &name)
{
    return Mi::itemType(name);
}

static int attributeRole(const QString &name)
{
    return Mi::itemDataRole(name);
}

static bool nextStartElement(QXmlStreamReader *reader)
{
    int tokenType = QXmlStreamReader::NoToken;
    while (tokenType != QXmlStreamReader::StartElement) {
        tokenType = reader->readNext();
        if (tokenType == QXmlStreamReader::Invalid)
            continue;
        if (reader->atEnd())
            return false;
    }
    return true;
}

static QXmlStreamReader::TokenType nextElement(QXmlStreamReader *reader)
{
    QXmlStreamReader::TokenType tokenType = QXmlStreamReader::NoToken;
    while (tokenType != QXmlStreamReader::StartElement
           && tokenType != QXmlStreamReader::EndElement) {
        tokenType = reader->readNext();
        if (reader->atEnd())
            return QXmlStreamReader::NoToken;
    }
    return tokenType;
}

static bool readItem(IModelItem *item, QXmlStreamReader *reader)
{
    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
    QString elementName = reader->name().toString();
    if (elementName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << ": Empty element name";
        return false;
    }
    if (elementName.endsWith("List")) {
        IModelList *list = query<IModelList>(item);
        QString listElementName = elementName;
        listElementName.chop(4);
        int itemType = elementType(listElementName);
        while (nextElement(reader) == QXmlStreamReader::StartElement) {
            IModelItem *newItem = query<IModelItem>(factory->create(itemType));
            list->append(newItem);
            if (!readItem(newItem, reader)) {
                qWarning() << Q_FUNC_INFO << ": failed to read list item in" << elementName;
                return false;
            }
        }
    } else {
        IModelData *data = query<IModelData>(item);
        if (!data) {
            qWarning() << Q_FUNC_INFO << ": Query IModelData failed in" << elementName;
            return false;
        }
        QXmlStreamAttributes attributes = reader->attributes();
        foreach (const QXmlStreamAttribute &attribute, attributes) {
            QString roleString = attribute.name().toString();
            int role = attributeRole(roleString);
            if (Mi::InvalidRole == role) {
                qWarning() << Q_FUNC_INFO << ": Invalid attribute role in" << elementName;
                return false;
            }
            data->set(attribute.value().toString(), role);
        }
        if (elementName.endsWith("Curve")) {
            PointList points;
            while (nextElement(reader) == QXmlStreamReader::StartElement) {
                Point point;
                QXmlStreamAttributes attributes = reader->attributes();
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
            data->set(QVariant::fromValue(points), Ac::PointsRole);
        } else {
            while (nextElement(reader) == QXmlStreamReader::StartElement) {
                QString subElementName = reader->name().toString();
                IModelItem *subItem = 0;
                if (subElementName.endsWith("List")) {
                    QString subElementListName = subElementName;
                    subElementListName.chop(4);
                    subItem = query<IModelItem>(item->findList(elementType(subElementListName)));
                } else
                    subItem = item->findItem(elementType(subElementName));
                if (!readItem(subItem, reader)) {
                    qWarning() << Q_FUNC_INFO << ": Sub-item read failed in" << elementName << "at" << subElementName;
                    return false;
                }
            }
        }
    }
    QString endElementName = reader->name().toString();
    if (endElementName != elementName)
        qWarning() << Q_FUNC_INFO << ": Mismatched element start and end tags (" << elementName << "-->" << endElementName << ")";
    return true;
}

namespace Ac {
namespace Core {

IAggregate *XmlReader::init()
{
    return this;
}

XmlReader::~XmlReader()
{
    delete _stream;
}

void XmlReader::setStream(QXmlStreamReader *stream)
{
    if (_stream == stream)
        return;
    delete _stream;
    _stream = stream;
}

int XmlReader::nextItemType()
{
    QXmlStreamReader *reader = stream();
    if (!reader)
        return -1;
    if (!nextStartElement(reader))
        return Mi::UnknownItem;
    const QString elementName = reader->name().toString();
    return elementType(elementName);
}

bool XmlReader::read(IModelItem *item)
{
    if (!item)
        return false;
    QXmlStreamReader *reader = stream();
    if (!reader)
        return false;
    if (!nextStartElement(reader))
        return false;
    return readItem(item, reader);
}

} // namespace Core
} // namespace Ac
