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

#ifndef AC_GUI_HORIZONTALGRIDLINE_GRAPHICSDATA_H
#define AC_GUI_HORIZONTALGRIDLINE_GRAPHICSDATA_H

#include "ac_gui_gridline_graphicsdata.h"

class QGraphicsLineItem;

namespace HorizontalGridLine {

class GraphicsData : public GridLine::GraphicsData
{
    QGraphicsLineItem *_editorSceneLineNode;
    QGraphicsLineItem *_editorSceneLineExtensionNode;

protected:
    GraphicsData(IAggregate *aggregate);
    ~GraphicsData();

    QGraphicsLineItem *editorSceneLineNode() const
    {
        return _editorSceneLineNode;
    }

    QGraphicsLineItem *editorSceneLineExtensionNode() const
    {
        return _editorSceneLineExtensionNode;
    }

    void update(int role, const QVariant &value);
};

}

#endif
