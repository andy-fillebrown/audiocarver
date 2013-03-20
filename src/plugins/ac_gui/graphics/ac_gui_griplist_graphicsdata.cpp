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

#include "ac_gui_griplist_graphicsdata.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <iaggregate.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <igraphicsentitydata.h>
#include <igraphicsitem.h>
#include <igraphicsiteminfo.h>
#include <igripdata.h>
#include <imodelitem.h>

using namespace Ac;

static bool gripLessThan(IGripData *a, IGripData *b)
{
    QPointF a_pos = a->position();
    QPointF b_pos = b->position();
    if (a_pos.x() < b_pos.x())
        return true;
    if (b_pos.x() < a_pos.x())
        return false;
    if (a_pos.y() < b_pos.y())
        return true;
    return false;
}

namespace GripList {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GripListData(aggregate)
    ,   _node(new GraphicsNode)
{
    _node->setVisible(false);
    _node->setZValue(Q_FLOAT_MAX);
}

GraphicsData::~GraphicsData()
{
//    delete _node;
}

void GraphicsData::initialize()
{
    IModelItem *root_item = IDatabase::instance()->rootItem();
    IGraphicsEntityData *root_gdata = QUERY(IGraphicsEntityData, root_item);
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    IGraphicsItemInfo *parent_ginfo = QUERY(IGraphicsItemInfo, this_gitem->parent());
    if (!parent_ginfo)
        return;
    QGraphicsItem *root_node = root_gdata->node(parent_ginfo->sceneType(), MainTransform);
    _node->setParentItem(root_node);
}

void GraphicsData::sort()
{
    qSort(_grips.begin(), _grips.end(), gripLessThan);
}

QGraphicsItem *GraphicsData::node() const
{
    return _node;
}

void GraphicsData::update(int role, const QVariant &value)
{
    if (HighlightRole == role)
        _node->setVisible(FullHighlight == qvariant_cast<int>(value));
    else if (PointsRole == role) {
        PointList points = qvariant_cast<PointList>(value);
        if (_grips.count() < points.count()) {
            IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
            IModelItem *this_item = QUERY(IModelItem, this);
            while (_grips.count() < points.count()) {
                IAggregate *grip = factory->create(GripItem, this_item);
                IGripData *grip_gdata = QUERY(IGripData, grip);
                QGraphicsItem *grip_node = grip_gdata->node();
                grip_node->setParentItem(_node);
                grip_node->setData(0, quintptr(grip));
                _grips.append(grip_gdata);
            }
        }
        while (points.count() < _grips.count()) {
            delete _grips.last();
            _grips.removeLast();
        }
        for (int i = 0;  i < _grips.count();  ++i) {
            IGraphicsData *grip_gdata = QUERY(IGraphicsData, _grips.at(i));
            const Point &point = points.at(i);
            grip_gdata->update(OriginalPositionRole, point.pos);
            grip_gdata->update(CurveTypeRole, point.curveType);
        }
    }
}

}
