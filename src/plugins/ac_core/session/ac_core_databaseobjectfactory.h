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

#ifndef AC_CORE_DATABASEOBJECTFACTORY_H
#define AC_CORE_DATABASEOBJECTFACTORY_H

#include <mi_core_base_databaseobjectfactory.h>
#include "ac_core_global.h"

namespace Core {

class AC_CORE_EXPORT DatabaseObjectFactory : public Base::DatabaseObjectFactory
{
protected:
    IAggregate *create(int itemType, IComponent *parent = 0);
    virtual void createComponents(int itemType, IAggregate *aggregate);
};

}

#endif
