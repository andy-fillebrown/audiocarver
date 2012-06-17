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

#ifndef AC_EDITOR_H
#define AC_EDITOR_H

#include "mi_editor.h"

#include <ac_igraphicsviewmanager.h>

namespace Ac {

class Editor : public Mi::Editor
{
    friend class GuiPlugin;

    QList<IGraphicsViewGroup*> _viewGroups;

protected:
    Editor()
    {}

    IAggregator *init();
    ~Editor();

    QList<IGraphicsViewGroup*> &viewGroups()
    {
        return _viewGroups;
    }

    // IEditor
    void undo();
    void redo();
    void cut();
    void copy() const;
    void paste();
    void selectAll();

    inline IAggregate *createAggregate(int interfaceType);
};

} // namespace Ac

inline IAggregate *Ac::Editor::createAggregate(int interfaceType)
{
    switch (interfaceType) {
    default:
        return Mi::Editor::createAggregate(interfaceType);
    }
}

#endif // AC_EDITOR_H
