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

#ifndef AC_GUI_GRIDSETTINGS_GRAPHICSITEM_H
#define AC_GUI_GRIDSETTINGS_GRAPHICSITEM_H

#include "ac_gui_base_graphicsitem.h"
#include <QMap>

namespace GridSettings {

class GraphicsItem : public Base::GraphicsItem
{
    QMap<int, QGraphicsItem*> _mainNodes;
    QMap<int, QGraphicsItem*> _unitXNodes;
    QMap<int, QGraphicsItem*> _unitYNodes;

public:
    GraphicsItem(IAggregate *aggregate);

protected:
    ~GraphicsItem();

    QGraphicsItem *findNode(int sceneType, int transformType) const;
};

}

#endif
