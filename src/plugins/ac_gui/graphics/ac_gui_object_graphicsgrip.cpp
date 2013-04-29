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

#include "ac_gui_object_graphicsgrip.h"
#include "ac_gui_constants.h"
#include "ac_gui_graphicsgripnode.h"
#include "ac_gui_gripselectionmodel.h"
#include <igraphicsitem.h>
#include <igraphicsgriplist.h>
#include <imodelitem.h>

using namespace Ac;
using namespace Qt;

namespace Object {

GraphicsGrip::GraphicsGrip(IAggregate *aggregate)
    :   Base::GraphicsGrip(aggregate)
    ,   _gripNode(0)
    ,   _curveType(NoCurve)
{
    _gripNode = new GraphicsGripNode;
}

GraphicsGrip::~GraphicsGrip()
{
    delete _gripNode;
}

void GraphicsGrip::initialize()
{
    IGraphicsItem *this_item = query<IGraphicsItem>(this);
    _gripNode->setData(0, quintptr(this_item));
    IGraphicsItem *parent_item = this_item->parent();
    IGraphicsGripList *parent_griplist = query<IGraphicsGripList>(parent_item);
    _gripNode->setParentItem(parent_griplist->findNode());
}

QPointF GraphicsGrip::originalPosition() const
{
    return _originalPosition;
}

QPointF GraphicsGrip::position() const
{
    return _gripNode->pos();
}

int GraphicsGrip::curveType() const
{
    return _curveType;
}

void GraphicsGrip::update(int role, const QVariant &value)
{
    GripSelectionModel *grip_ss_model = GripSelectionModel::instance();
    switch (role) {
    case HighlightRole: {
        const int highlight_type = qvariant_cast<int>(value);
        _gripNode->highlight(highlight_type);
        if (FullHighlight == highlight_type)
            grip_ss_model->appendGrip(this);
        else
            grip_ss_model->removeGrip(this);
    }   return;
    case OriginalPositionRole:
        _originalPosition = qvariant_cast<QPointF>(value);
    case PositionRole: {
        QPointF pos = qvariant_cast<QPointF>(value);
        _gripNode->setPos(pos);
    }   break;
    case CurveTypeRole:
        _curveType = qvariant_cast<int>(value);
        break;
    case VisibilityRole:
        _gripNode->setVisible(qvariant_cast<bool>(value));
    }
    grip_ss_model->update();
}

}
