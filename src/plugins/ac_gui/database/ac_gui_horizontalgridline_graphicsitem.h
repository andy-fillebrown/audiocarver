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

#ifndef AC_GUI_HORIZONTALGRIDLINE_GRAPHICSITEM_H
#define AC_GUI_HORIZONTALGRIDLINE_GRAPHICSITEM_H

#include "ac_gui_gridline_graphicsitem.h"

class QGraphicsLineItem;

namespace HorizontalGridLine {

class GraphicsItem : public GridLine::GraphicsItem
{
    QGraphicsLineItem *_editorSceneLineNode;
    QGraphicsLineItem *_editorSceneLineExtensionNode;

protected:
    GraphicsItem(IAggregate *aggregate)
        :   GridLine::GraphicsItem(aggregate)
        ,   _editorSceneLineNode(0)
        ,   _editorSceneLineExtensionNode(0)
    {}

    QGraphicsLineItem *editorSceneLineNode() const
    {
        return _editorSceneLineNode;
    }

    QGraphicsLineItem *editorSceneLineExtensionNode() const
    {
        return _editorSceneLineExtensionNode;
    }

    virtual IUnknown *initialize();
    ~GraphicsItem();

    void setColor(int color);
    void update(int role);
};

}

#endif
