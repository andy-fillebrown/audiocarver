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

#ifndef AC_GUI_CURVE_GRAPHICSITEM_H
#define AC_GUI_CURVE_GRAPHICSITEM_H

#include "ac_gui_object_graphicsitem.h"

class GraphicsCurveNode;

namespace Curve {

class GraphicsItem : public Object::GraphicsItem
{
    GraphicsCurveNode *_curveNode;

public:
    GraphicsItem(IAggregate *aggregate);

protected:
    ~GraphicsItem();

    int transformType() const;
    bool intersects(const QRectF &rect) const;
    QGraphicsItem *findNode(int sceneType, int transformType) const;
    void update(int role, const QVariant &value);
};

}

#endif
