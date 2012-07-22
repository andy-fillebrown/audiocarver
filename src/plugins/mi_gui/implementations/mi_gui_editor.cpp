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

#include <mi_iaggregate.h>

static IEditor *instance = 0;

IEditor *IEditor::instance()
{
    return ::instance;
}

namespace Mi {
namespace Gui {

void Editor::destroy()
{
    delete ::instance;
    ::instance = 0;
}

Editor::Editor()
    :   _isInCommand(false)
{
    if (::instance)
        delete ::instance;
    ::instance = this;
}

IAggregator *Editor::init()
{
    return this;
}

Editor::~Editor()
{
    clear();
}

IAggregate *Editor::appendAggregate(IAggregate *aggregate)
{
    const int interface_type = aggregate->interfaceType();
    if (!_aggregates.contains(interface_type))
        _aggregates.insert(interface_type, aggregate);
    return aggregate;
}

void Editor::removeAggregate(IAggregate *aggregate)
{
    _aggregates.remove(aggregate->interfaceType());
}

void Editor::clear()
{
    qDeleteAll(_aggregates);
    _aggregates.clear();
}

} // namespace Gui
} // namespace Mi
