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

#ifndef AC_GUI_GRIDLINE_GRAPHICSITEM_H
#define AC_GUI_GRIDLINE_GRAPHICSITEM_H

#include "ac_gui_object_graphicsentity.h"
#include <qnamespace.h>

class GraphicsNode;
class GraphicsTextNode;
class QFont;

namespace GridLine {

class GraphicsItem : public Object::GraphicsEntity
{
    GraphicsNode *_labelSceneRootNode;
    GraphicsTextNode *_labelSceneTextNode;

protected:
    static const QFont &gridLabelFont();
    static Qt::PenStyle gridLinePenStyle();
    static Qt::PenStyle gridLineExtensionPenStyle();

    GraphicsItem(IAggregate *aggregate);
    ~GraphicsItem();

    GraphicsNode *labelSceneRootNode() const
    {
        return _labelSceneRootNode;
    }

    GraphicsTextNode *labelSceneTextNode() const
    {
        return _labelSceneTextNode;
    }

    void setColor(int color);
    void update(int role);

    void highlight(bool on)
    {}
};

}

#endif
