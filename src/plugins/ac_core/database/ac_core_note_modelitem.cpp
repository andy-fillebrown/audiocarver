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

#include "ac_core_note_modelitem.h"
#include "ac_core_namespace.h"

using namespace Ac;

namespace Note {

IUnknown *ModelItem::initialize()
{
    return ScoreObject::ModelItem::initialize();
}

int ModelItem::itemType() const
{
    return NoteItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (NoteItem == itemType)
        return true;
    return ScoreObject::ModelItem::isTypeOfItem(itemType);
}

}
