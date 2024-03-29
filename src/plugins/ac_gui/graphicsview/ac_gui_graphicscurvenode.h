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

#ifndef AC_GUI_GRAPHICSCURVENODE_H
#define AC_GUI_GRAPHICSCURVENODE_H

#include "ac_gui_graphicspathnode.h"
#include <ac_core_point.h>

class GraphicsGuideNode;
class IGraphicsItem;

class GraphicsCurveNode : public GraphicsPathNode
{
    GraphicsGuideNode *_guide;
    QGraphicsRectItem *_noteHead;

public:
    GraphicsCurveNode(QGraphicsItem *parent = 0);

    bool intersects(const QRectF &rect) const;
    void setGraphicsItem(IGraphicsItem *graphicsItem);
    void setPoints(const PointList &points);
    void setColor(const QColor &color);
    void highlight(bool on);
};

#endif
