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

#ifndef AC_GUI_DATABASEOBJECTFACTORY_H
#define AC_GUI_DATABASEOBJECTFACTORY_H

#include <ac_core_databaseobjectfactory.h>

namespace Gui {

class DatabaseObjectFactory : public Core::DatabaseObjectFactory
{
protected:
    void createComponents(int itemType, IAggregate *aggregate);
};

}

#endif
