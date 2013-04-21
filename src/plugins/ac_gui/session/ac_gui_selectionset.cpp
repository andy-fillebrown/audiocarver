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

#include "ac_gui_selectionset.h"
#include <mi_gui_scopedselectionchange.h>

namespace Gui {

bool SelectionSet::append(IGraphicsItem *item)
{
    if (_items.contains(item))
        return false;
    ScopedSelectionChange scoped_selection_change(this);
    _items.append(item);
    return true;
}

bool SelectionSet::append(const QList<IGraphicsItem*> &items)
{
    bool items_to_append = false;
    foreach (IGraphicsItem *item, items) {
        if (_items.contains(item))
            continue;
        items_to_append = true;
        break;
    }
    if (!items_to_append)
        return false;
    ScopedSelectionChange scoped_selection_change(this);
    foreach (IGraphicsItem *item, items) {
        if (_items.contains(item))
            continue;
        _items.append(item);
    }
    return true;
}

bool SelectionSet::remove(IGraphicsItem *item)
{
    if (!_items.contains(item))
        return false;
    ScopedSelectionChange scoped_selection_change(this);
    _items.removeOne(item);
    return true;
}

bool SelectionSet::remove(const QList<IGraphicsItem*> &items)
{
    bool items_to_remove = false;
    foreach (IGraphicsItem *item, items) {
        if (!_items.contains(item))
            continue;
        items_to_remove = true;
        break;
    }
    if (!items_to_remove)
        return false;
    ScopedSelectionChange scoped_selection_change(this);
    foreach (IGraphicsItem *item, items)
        _items.removeOne(item);
    return true;
}

void SelectionSet::clear()
{
    if (_items.isEmpty())
        return;
    ScopedSelectionChange scoped_selection_change(this);
    _items.clear();
}

}
