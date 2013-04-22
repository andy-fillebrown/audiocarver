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

#ifndef AC_GUI_CURVE_GRAPHICSGRIPLIST_H
#define AC_GUI_CURVE_GRAPHICSGRIPLIST_H

#include "ac_gui_object_graphicsgriplist.h"
#include <QList>

namespace Curve {

class GraphicsGripList : public Object::GraphicsGripList
{
    QList<IGraphicsGrip*> _grips;

public:
    GraphicsGripList(IAggregate *aggregate)
        :   Object::GraphicsGripList(aggregate)
    {}

protected:
    ~GraphicsGripList();

    QList<IGraphicsGrip*> grips() const
    {
        return _grips;
    }

    void sort();
    void update(int role, const QVariant &value);
};

}

#endif
