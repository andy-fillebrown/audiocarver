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

#ifndef MI_CORE_OBJECT_MODELITEMINFO_H
#define MI_CORE_OBJECT_MODELITEMINFO_H

#include "mi_core_base_modeliteminfo.h"

namespace Object {

class MI_CORE_EXPORT ModelItemInfo : public Base::ModelItemInfo
{
protected:
    ModelItemInfo(IAggregate *aggregate)
        :   Base::ModelItemInfo(aggregate)
    {}

    int itemType() const;

    bool isTypeOfItem(int itemType) const
    {
        return false;
    }
};

}

#endif
