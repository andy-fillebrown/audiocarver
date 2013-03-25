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

#ifndef AC_GUI_VELOCITY_GRIPLISTDATA_H
#define AC_GUI_VELOCITY_GRIPLISTDATA_H

#include "ac_gui_object_griplistdata.h"

namespace Velocity {

class GripListData : public Object::GripListData
{
    IGripData *_grip;

public:
    GripListData(IAggregate *aggregate)
        :   Object::GripListData(aggregate)
    {}

protected:
    ~GripListData();

    void initialize();

    QList<IGripData*> grips() const
    {
        QList<IGripData*> griplist;
        griplist.append(_grip);
        return griplist;
    }

    void sort()
    {}

    void update(int role, const QVariant &value);
};

}

#endif
