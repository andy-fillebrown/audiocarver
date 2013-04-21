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

#ifndef AC_GUI_SELECTIONSET_H
#define AC_GUI_SELECTIONSET_H

#include <mi_gui_base_selectionset.h>
#include <QList>

namespace Gui {

class SelectionSet : public Base::SelectionSet
{
    QList<IGraphicsItem*> _items;

public:
    SelectionSet(IAggregate *aggregate)
        :   Base::SelectionSet(aggregate)
    {}

protected:
    const QList<IGraphicsItem*> &items() const
    {
        return _items;
    }

    bool append(IGraphicsItem *item);
    bool append(const QList<IGraphicsItem*> &items);
    bool remove(IGraphicsItem *item);
    bool remove(const QList<IGraphicsItem*> &items);
    void clear();
};

}

#endif
