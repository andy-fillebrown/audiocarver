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

#include "mi_gui_base_undomanager.h"
#include <iaggregate.h>
#include <isession.h>

static IUndoManager *instance = 0;

IUndoManager *IUndoManager::instance()
{
    return ::instance;
}

namespace Base {

UndoManager::UndoManager()
{
    IAggregate *aggregate = ISession::instance();
    aggregate->removeComponent(::instance);
    delete ::instance;
    ::instance = this;
    aggregate->appendComponent(this);
}

UndoManager::~UndoManager()
{
    ::instance = 0;
}

void *UndoManager::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : ISession::instance()->queryInterface(interfaceType);
}

}
