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

#include "ac_core_writer.h"
#include "ac_core_namespace.h"
#include "ac_core_point.h"
#include <iaggregate.h>
#include <ifiler.h>
#include <imodelitem.h>
#include <QFile>
#include <QXmlStreamWriter>

using namespace Mi;
using namespace Ac;

namespace Xml {

static void writePoints(const PointList &points, QXmlStreamWriter *writer)
{
    if (points.isEmpty())
        return;
    foreach (const Point &pt, points) {
        writer->writeStartElement("Point");
        const QPointF &pos = pt.pos;
        writer->writeAttribute("position", QString("%1 %2").arg(pos.x()).arg(pos.y()));
        if (BezierCurve == pt.curveType)
            writer->writeAttribute("curve", "bezier");
        writer->writeEndElement();
    }
}

static void writeItemData(IModelItem *item, int roleIndex, QXmlStreamWriter *writer)
{
    int role = item->roleAt(roleIndex);
    QVariant data = item->getValue(role);
    if (PointsRole == role)
        writePoints(data.value<PointList>(), writer);
    else {
        QString data_string = data.toString();
        if (!data_string.isEmpty())
            writer->writeAttribute(itemDataRoleString(role), data_string);
    }
}

static bool writeItem(IModelItem *item, QXmlStreamWriter *writer)
{
    if (!item)
        return false;
    QString element_name;
    if (item->isTypeOfItem(ListItem)) {
        if (0 == item->itemCount())
            return true;
        element_name = itemTypeString(get<int>(item, ListTypeRole)) + "List";
    } else
        element_name = itemTypeString(item->itemType());
    if (item->isTypeOfItem(CurveItem) && get<PointList>(item, PointsRole).isEmpty())
        return true;
    writer->writeStartElement(element_name);
    int role_count = item->roleCount();
    for (int i = 0;  i < role_count;  ++i)
        writeItemData(item, i, writer);
    int item_count = item->itemCount();
    for (int i = 0;  i < item_count;  ++i)
        if (!writeItem(item->itemAt(i), writer))
            return false;
    writer->writeEndElement();
    return true;
}

Writer::Writer(IAggregate *aggregate)
    :   _aggregate(aggregate)
    ,   _writer(0)
{
    _aggregate->appendComponent(this);
}

void *Writer::queryInterface(int interfaceType) const
{
    void *i = IWriter::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

bool Writer::writeStartElement(const QString &elementName)
{
    if (!_writer)
        _writer = query<IFiler>(this)->writer();
    if (!_writer)
        return false;
    _writer->writeStartElement(elementName);
    return true;
}

bool Writer::writeEndElement()
{
    if (!_writer)
        return false;
    _writer->writeEndElement();
    return true;
}

bool Writer::write(IModelItem *item)
{
    if (!item)
        return false;
    if (!_writer)
        _writer = query<IFiler>(this)->writer();
    if (!_writer)
        return false;
    if (writeItem(item, _writer)) {
        _writer->writeCharacters("\n");
        return true;
    }
    return false;
}

}
