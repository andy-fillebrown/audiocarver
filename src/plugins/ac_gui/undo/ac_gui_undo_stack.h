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

#ifndef AC_UNDO_STACK_H
#define AC_UNDO_STACK_H

#include <mi_gui_undo_stack.h>

namespace Ac {
namespace Undo {

class Stack : public ::Undo::Stack
{
public:
    Stack(QObject *parent = 0)
        :   ::Undo::Stack(parent)
    {}

private slots:
    void dataAboutToBeChanged(IModelItem *item, int role);
    void dataChanged(IModelItem *item, int role);
};

}
}

#endif
