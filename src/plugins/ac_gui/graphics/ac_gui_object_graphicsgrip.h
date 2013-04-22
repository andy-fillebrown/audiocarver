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

#ifndef AC_GUI_OBJECT_GRAPHICSGRIP_H
#define AC_GUI_OBJECT_GRAPHICSGRIP_H

#include "ac_gui_base_graphicsgrip.h"
#include <QPointF>

class GraphicsGripNode;

namespace Object {

class GraphicsGrip : public Base::GraphicsGrip
{
    GraphicsGripNode *_gripNode;
    int _curveType;
    QPointF _originalPosition;

public:
    GraphicsGrip(IAggregate *aggregate);

protected:
    ~GraphicsGrip();

    void initialize();
    QPointF originalPosition() const;
    QPointF position() const;
    int curveType() const;
    void update(int role, const QVariant &value);
};

}

#endif
