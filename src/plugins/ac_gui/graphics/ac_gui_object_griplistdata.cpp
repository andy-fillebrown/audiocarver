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

#include "ac_gui_object_griplistdata.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <idatabase.h>
#include <igraphicsdata.h>
#include <igraphicsitem.h>
#include <igraphicsiteminfo.h>
#include <igripdata.h>
#include <imodeldata.h>
#include <imodelitem.h>

using namespace Ac;

namespace Object {

GripListData::GripListData(IAggregate *aggregate)
    :   Base::GripListData(aggregate)
    ,   _node(new GraphicsNode)
{
    _node->setVisible(false);
    _node->setZValue(Q_FLOAT_MAX);
}

void GripListData::initialize()
{
    IModelItem *root_item = IDatabase::instance()->rootItem();
    IGraphicsData *root_gdata = QUERY(IGraphicsData, root_item);
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    IGraphicsItemInfo *parent_ginfo = QUERY(IGraphicsItemInfo, this_gitem->parent());
    if (!parent_ginfo)
        return;
    QGraphicsItem *root_node = root_gdata->findNode(parent_ginfo->sceneType(), MainTransform);
    _node->setParentItem(root_node);
}

QGraphicsItem *GripListData::findNode(int sceneType, int transformType) const
{
    Q_ASSERT(UnspecifiedScene == sceneType);
    Q_ASSERT(UnspecifiedTransform == transformType);
    return _node;
}

void GripListData::update(int role, const QVariant &value)
{
    if (HighlightRole == role)
        _node->setVisible(FullHighlight == qvariant_cast<int>(value));
}

}
