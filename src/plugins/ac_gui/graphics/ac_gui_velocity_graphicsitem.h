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

#ifndef AC_GUI_VELOCITY_GRAPHICSITEM_H
#define AC_GUI_VELOCITY_GRAPHICSITEM_H

#include "ac_gui_base_graphicsitem.h"

class QGraphicsLineItem;

namespace Object {
class Aggregate;
}

namespace Velocity {

class GraphicsItem : public Base::GraphicsItem
{
    IAggregate *_grips;
    QGraphicsLineItem *_lineNode;

public:
    GraphicsItem(IAggregate *aggregate);

protected:
    ~GraphicsItem();
    void initialize();

    Object::Aggregate *aggregate() const;

    int sceneType() const;
    int transformType() const;
    bool intersects(const QRectF &rect) const;
    IGraphicsItem *parent() const;
    QGraphicsItem *findNode(int sceneType, int transformType) const;
    void update(int role, const QVariant &value);
};

}

#endif
