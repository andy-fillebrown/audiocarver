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

#ifndef AC_GUI_GRIP_GRAPHICSDATA_H
#define AC_GUI_GRIP_GRAPHICSDATA_H

#include "ac_gui_base_gripdata.h"
#include <QPointF>

class GraphicsGripNode;

namespace Grip {

class GraphicsData : public Base::GripData
{
    GraphicsGripNode *_gripNode;
    int _curveType;
    QPointF _originalPosition;

public:
    GraphicsData(IAggregate *aggregate);

protected:
    ~GraphicsData();

    void initialize();
    QPointF originalPosition() const;
    QPointF position() const;
    int curveType() const;
    QGraphicsItem *findNode(int sceneType, int transformType) const;
    void update(int role, const QVariant &value);
};

}

#endif
