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
#include <imodelitem.h>

using namespace Ac;

namespace Note {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   ScoreObject::GraphicsItem(aggregate)
    ,   _velocity(0)
{}

GraphicsItem::~GraphicsItem()
{
    delete _velocity;
}

void GraphicsItem::initialize()
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    IModelItem *this_item = QUERY(IModelItem, this);
    Q_ASSERT(this_item);
    _velocity = factory->create(VelocityItem, this_item);
}

QList<IGraphicsItem*> GraphicsItem::subentities(int sceneType, int transformType) const
{
    QList<IGraphicsItem*> subents = ScoreObject::GraphicsItem::subentities(sceneType, transformType);
    if (ControlScene == sceneType && MainTransform == transformType) {
        IGraphicsItem *velocity_gitem = QUERY(IGraphicsItem, _velocity);
        if (velocity_gitem)
            subents.append(velocity_gitem);
    }
    return subents;
}

}
