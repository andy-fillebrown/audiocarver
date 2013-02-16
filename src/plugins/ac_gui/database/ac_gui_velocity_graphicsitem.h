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

#ifndef AC_GUI_VELOCITY_GRAPHICSITEM_H
#define AC_GUI_VELOCITY_GRAPHICSITEM_H

#include <igraphicscurve.h>

class IAggregate;
class IModelItem;
class QGraphicsLineItem;

namespace Velocity {

class GraphicsItem : public IGraphicsCurve
{
    IAggregate *_aggregate;
    QGraphicsLineItem *_lineNode;

public:
    void *queryInterface(int interfaceType) const;

    GraphicsItem(IAggregate *aggregate)
        :   _aggregate(aggregate)
        ,   _lineNode(0)
    {}

    virtual IUnknown *initialize();

protected:
    ~GraphicsItem();

    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    QGraphicsItem *node(int sceneType, int transformType) const;
    void setColor(int color);
    void setPoints(const PointList &points);
    bool intersects(const QRectF &rect) const;
    void highlight(bool on);
    bool isVisible() const;
    virtual void update(int role);

    IModelItem *parent() const;
};

}

#endif
