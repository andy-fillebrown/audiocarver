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

#ifndef AC_GUI_SCORE_GRAPHICSITEM_H
#define AC_GUI_SCORE_GRAPHICSITEM_H

#include "ac_gui_scoreobject_graphicsitem.h"

namespace Score {

class Aggregate;

class GraphicsItem : public ScoreObject::GraphicsItem
{
    IAggregate *_playCursor;

public:
    GraphicsItem(IAggregate *aggregate);
    ~GraphicsItem();

protected:
    QMap<int, QGraphicsItem*> _unitXNodes;
    QMap<int, QGraphicsItem*> _unitYNodes;

    QGraphicsItem *findNode(int sceneType, int transformType) const;

    int itemCount() const
    {
        return ScoreObject::GraphicsItem::itemCount() + 1;
    }

    IGraphicsItem *itemAt(int i) const;
    IGraphicsItem *findItem(int itemType) const;
    void update(int role, const QVariant &value);
};

}

#endif
