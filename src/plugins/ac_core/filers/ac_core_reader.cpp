/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_core_reader.h"
#include "ac_core_namespace.h"
#include "ac_core_point.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>
#include <ifilefiler.h>
#include <imodelitem.h>
#include <QFile>
#include <QStringList>
#include <QXmlStreamReader>

#include <QtDebug>

using namespace Mi;
using namespace Ac;

namespace Xml {

static int elementType(const QString &name)
{
    return itemType(name);
}

static int attributeRole(const QString &name)
{
    return itemDataRole(name);
}

static bool nextStartElement(QXmlStreamReader *reader)
{
    int token_type = QXmlStreamReader::NoToken;
    while (token_type != QXmlStreamReader::StartElement) {
        token_type = reader->readNext();
        if (token_type == QXmlStreamReader::Invalid)
            continue;
        if (reader->atEnd())
            return false;
    }
    return true;
}

static QXmlStreamReader::TokenType nextElement(QXmlStreamReader *reader)
{
    QXmlStreamReader::TokenType token_type = QXmlStreamReader::NoToken;
    while (token_type != QXmlStreamReader::StartElement
           && token_type != QXmlStreamReader::EndElement) {
        token_type = reader->readNext();
        if (reader->atEnd())
            return QXmlStreamReader::NoToken;
    }
    return token_type;
}

static bool readItem(IModelItem *item, QXmlStreamReader *reader)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    QString element_name = reader->name().toString();
    if (element_name.isEmpty()) {
        qWarning() << Q_FUNC_INFO << ": Empty element name";
        return false;
    }
    if (element_name.endsWith("List")) {
        QString list_element_name = element_name;
        list_element_name.chop(4);
        int item_type = elementType(list_element_name);
        while (nextElement(reader) == QXmlStreamReader::StartElement) {
            IModelItem *new_item = query<IModelItem>(factory->create(item_type));
            item->appendItem(new_item);
            if (!readItem(new_item, reader)) {
                qWarning() << Q_FUNC_INFO << ": failed to read list item in" << element_name;
                return false;
            }
        }
    } else {
        QXmlStreamAttributes attributes = reader->attributes();
        foreach (const QXmlStreamAttribute &attribute, attributes) {
            int role = attributeRole(attribute.name().toString());
            if (InvalidRole == role) {
                qWarning() << Q_FUNC_INFO << ": Invalid attribute role in" << element_name;
                return false;
            }
            item->set(role, attribute.value().toString());
        }
        if (element_name.endsWith("Curve")) {
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
                        point.curveType = BezierCurve;
                }
                points.append(point);
                nextElement(reader);
            }
            item->set(PointsRole, QVariant::fromValue(points));
        } else {
            while (nextElement(reader) == QXmlStreamReader::StartElement) {
                QString sub_element_name = reader->name().toString();
                IModelItem *sub_item = item->findItem(elementType(sub_element_name));
                if (!readItem(sub_item, reader)) {
                    qWarning() << Q_FUNC_INFO << ": Sub-item read failed in" << element_name << "at" << sub_element_name;
                    return false;
                }
            }
        }
    }
    QString end_element_name = reader->name().toString();
    if (end_element_name != element_name)
        qWarning() << Q_FUNC_INFO << ": Mismatched element start and end tags (" << element_name << "-->" << end_element_name << ")";
    return true;
}

Reader::Reader(IAggregate *aggregate)
    :   _aggregate(aggregate)
    ,   _stream(0)
{
    _aggregate->appendComponent(this);
}

Reader::~Reader()
{
    delete _stream;
}

void *Reader::queryInterface(int interfaceType) const
{
    void *i = IReader::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

void Reader::setStream(QXmlStreamReader *stream)
{
    if (_stream == stream)
        return;
    delete _stream;
    _stream = stream;
}

int Reader::nextItemType()
{
    QXmlStreamReader *reader = _stream;
    if (!reader)
        return -1;
    if (!nextStartElement(reader))
        return UnknownItem;
    const QString element_name = reader->name().toString();
    return elementType(element_name);
}

bool Reader::read(IModelItem *item)
{
    if (!item)
        return false;
    QFile *file = query<IFileFiler>(this)->file();
    if (file && file->open(QIODevice::ReadOnly))
        setStream(new QXmlStreamReader(file));
    QXmlStreamReader *reader = _stream;
    if (!reader)
        return false;
    if (!nextStartElement(reader))
        return false;
    return readItem(item, reader);
}

}
