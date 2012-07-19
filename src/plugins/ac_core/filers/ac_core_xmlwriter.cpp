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

#include "ac_core_xmlwriter.h"

#include <mi_imodeldata.h>
#include <mi_imodellist.h>

#include <ac_core_point.h>

#include <QXmlStreamWriter>

using namespace Mi;

namespace Ac {
namespace Core {

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

static void writeItemData(IModelData *data, int roleIndex, QXmlStreamWriter *writer)
{
    int role = data->roleAt(roleIndex);
    QVariant variant = data->getVariant(role);
    if (PointsRole == role)
        writePoints(variant.value<PointList>(), writer);
    else {
        QString value_string = variant.toString();
        if (!value_string.isEmpty())
            writer->writeAttribute(itemDataRoleString(role), value_string);
    }
}

static bool writeItem(IModelItem *item, QXmlStreamWriter *writer)
{
    IModelData *data = query<IModelData>(item);
    if (data) {
        if (item->isTypeOfItem(CurveItem) && data->get<PointList>(PointsRole).isEmpty())
            return true;
        writer->writeStartElement(itemTypeString(item->itemType()));
        int roleCount = data->roleCount();
        for (int i = 0;  i < roleCount;  ++i)
            writeItemData(data, i, writer);
    } else {
        if (item->isTypeOfItem(ListItem)) {
            if (0 == item->count())
                return true;
            writer->writeStartElement(itemTypeString(query<IModelList>(item)->listType()) + "List");
        } else
            writer->writeStartElement(itemTypeString(item->itemType()));
    }
    int item_count = item->count();
    for (int i = 0;  i < item_count;  ++i)
        if (!writeItem(item->at(i), writer))
            return false;
    writer->writeEndElement();
    return true;
}

IAggregate *XmlWriter::init()
{
    return this;
}

XmlWriter::~XmlWriter()
{
    if (_stream)
        _stream->device()->write("\n");
    delete _stream;
}

void XmlWriter::setStream(QXmlStreamWriter *stream)
{
    if (_stream == stream)
        return;
    delete _stream;
    _stream = stream;
    _stream->setAutoFormatting(true);
}

bool XmlWriter::write(IModelItem *item)
{
    if (!item)
        return false;
    QXmlStreamWriter *writer = stream();
    if (!writer)
        return false;
    return writeItem(item, writer);
}

} // namespace Core
} // namespace Ac
