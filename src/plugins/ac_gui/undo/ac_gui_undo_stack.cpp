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

#include "ac_gui_undo_stack.h"
#include <ac_core_namespace.h>

namespace Ac {
namespace Undo {

void Stack::dataAboutToBeChanged(IModelItem *item, int role)
{
    if (PlaybackTimeRole == role)
        return;
    ::Undo::Stack::dataAboutToBeChanged(item, role);
}

void Stack::dataChanged(IModelItem *item, int role)
{
    if (PlaybackTimeRole == role)
        return;
    ::Undo::Stack::dataChanged(item, role);
}

}
}
