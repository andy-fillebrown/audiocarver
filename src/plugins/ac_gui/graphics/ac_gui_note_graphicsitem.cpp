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

#include "ac_gui_note_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace Note {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   ScoreObject::GraphicsItem(aggregate)
    ,   _velocity(0)
{
    _velocity = IDatabaseObjectFactory::instance()->create(VelocityItem, aggregate);
}

GraphicsItem::~GraphicsItem()
{
    qDelete(_velocity);
}

IGraphicsItem *GraphicsItem::itemAt(int i) const
{
    if (2 == i)
        return query<IGraphicsItem>(_velocity);
    return ScoreObject::GraphicsItem::itemAt(i);
}

IGraphicsItem *GraphicsItem::findItem(int itemType) const
{
    if (VelocityItem == itemType)
        return query<IGraphicsItem>(_velocity);
    return ScoreObject::GraphicsItem::findItem(itemType);
}

void GraphicsItem::update(int role, const QVariant &value)
{
    if (ColorRole == role
            || VolumeRole == role
            || HighlightRole == role) {
        findItem(PitchCurveItem)->update(role, value);
        findItem(VelocityItem)->update(role, value);
    }
}

}
