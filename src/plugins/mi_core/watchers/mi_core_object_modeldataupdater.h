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

#ifndef MI_CORE_OBJECT_MODELDATAUPDATER_H
#define MI_CORE_OBJECT_MODELDATAUPDATER_H

#include "mi_core_base_modeldatawatcher.h"

namespace Object {

class MI_CORE_EXPORT ModelDataUpdater : public Base::ModelDataWatcher
{
public:
    ModelDataUpdater(IAggregate *aggregate)
        :   Base::ModelDataWatcher(aggregate)
    {}

protected:
    void beginChangeData(const IModelData *data, int role, int changeType);
    void endChangeData(const IModelData *data, int role, int changeType);
};

}

#endif
