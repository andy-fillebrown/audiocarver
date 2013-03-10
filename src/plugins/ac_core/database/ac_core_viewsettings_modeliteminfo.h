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

#ifndef AC_CORE_VIEWSETTINGS_MODELITEMINFO_H
#define AC_CORE_VIEWSETTINGS_MODELITEMINFO_H

#include <mi_core_object_modeliteminfo.h>

namespace ViewSettings {

class ModelItemInfo : public Object::ModelItemInfo
{
public:
    ModelItemInfo(IAggregate *aggregate)
        :   Object::ModelItemInfo(aggregate)
    {}

protected:
    int itemType() const;
    bool isTypeOfItem(int itemType) const;
};

}

#endif
