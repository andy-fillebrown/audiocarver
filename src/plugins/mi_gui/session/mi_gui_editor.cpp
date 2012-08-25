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

#include "mi_gui_editor.h"
#include <iaggregate.h>
#include <isession.h>

static IEditor *instance = 0;

IEditor *IEditor::instance()
{
    return ::instance;
}

namespace Base {

Editor::Editor()
    :   _isInCommand(false)
{
    ISession::instance()->remove(::instance);
    delete ::instance;
    ::instance = this;
}

IUnknown *Editor::initialize()
{
    return ISession::instance()->append(this);
}

Editor::~Editor()
{
    ::instance = 0;
}

void *Editor::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<Editor*>(this);
    return ISession::instance()->queryInterface(interfaceType);
}

}
