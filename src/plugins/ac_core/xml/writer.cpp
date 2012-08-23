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

#include "writer.h"
#include <interfaces/iaggregate.h>
#include <interfaces/ifilefiler.h>
#include <interfaces/imodeldata.h>
#include <interfaces/imodelitemlist.h>
#include <tools/point.h>
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

static void writeItemData(IModelData *data, int roleIndex, QXmlStreamWriter *writer)
{
    int role = data->roleAt(roleIndex);
    QVariant variant = data->getValue(role);
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
        if (item->isList()) {
            if (0 == item->count())
                return true;
            writer->writeStartElement(itemTypeString(query<IModelItemList>(item)->listType()) + "List");
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

IUnknown *Writer::initialize()
{
    aggregate()->append(this);
    return this;
}

Writer::~Writer()
{
    delete _stream;
}

void *Writer::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<Writer*>(this);
    return aggregate()->queryInterface(interfaceType);
}

void Writer::setStream(QXmlStreamWriter *stream)
{
    if (_stream == stream)
        return;
    delete _stream;
    _stream = stream;
    _stream->setAutoFormatting(true);
}

bool Writer::write(IModelItem *item)
{
    if (!item)
        return false;
    QFile *file = query<IFileFiler>(this)->file();
    if (file && file->open(QIODevice::WriteOnly))
        setStream(new QXmlStreamWriter(file));
    QXmlStreamWriter *writer = stream();
    if (!writer)
        return false;
    if (writeItem(item, writer)) {
        writer->writeCharacters("\n");
        return true;
    }
    return false;
}

}
