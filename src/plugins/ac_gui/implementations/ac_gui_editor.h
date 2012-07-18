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

#ifndef AC_GUI_EDITOR_H
#define AC_GUI_EDITOR_H

#include "mi_gui_editor.h"

#include <ac_igraphicsviewmanager.h>

namespace Ac {

class GuiPlugin;

namespace Gui {

class Editor : public Mi::Gui::Editor
{
    friend class Ac::GuiPlugin;
    friend class ViewManager;

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

class ViewManager : public IGraphicsViewManager
{
    friend class Editor;

    Editor *_aggregator;

protected:
    Editor *a() const
    {
        return _aggregator;
    }

    ViewManager(Editor *aggregator)
        :   _aggregator(aggregator)
    {}

    IAggregate *init();

    // IGraphicsViewManager
    int count() const
    {
        return a()->viewGroups().count();
    }

    IGraphicsViewGroup *at(int i) const
    {
        return a()->viewGroups().at(i);
    }

    void append(IGraphicsViewGroup *group)
    {
        QList<IGraphicsViewGroup*> &viewGroups = a()->viewGroups();
        if (viewGroups.contains(group))
            return;
        viewGroups.append(group);
    }

    void remove(IGraphicsViewGroup *group)
    {
        a()->viewGroups().removeOne(group);
    }

    // IAggregate
    IAggregator *aggregator() const
    {
        return _aggregator;
    }
};

inline IAggregate *Editor::createAggregate(int interfaceType)
{
    switch (interfaceType) {
    case I::IGraphicsViewManager:
        return appendAggregate((new ViewManager(this))->init());
    default:
        return 0;
    }
}

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_EDITOR_H
