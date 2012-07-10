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

#include "ac_gui_database.h"

#include "ac_gui_filerfactory.h"

namespace Ac {
namespace Gui {

using namespace Database;

IAggregator *Database::init()
{
    return Ac::Database::init();
}

IAggregate *Database::createAggregate(int interfaceType)
{
    switch (interfaceType) {
    case I::IFilerFactory:
        return appendAggregate((new FilerFactory(this))->init());
    default:
        return Ac::Database::createAggregate(interfaceType);
    }
}

} // namespace Gui
} // namespace Ac
