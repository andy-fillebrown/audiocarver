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

#ifndef MI_GUI_EDITOR_H
#define MI_GUI_EDITOR_H

#include "mi_ieditor.h"

namespace Mi {

class GuiPlugin;

namespace Gui {

class MI_GUI_EXPORT Editor : public IEditor
{
    friend class Mi::GuiPlugin;

    static IEditor *instance()
    {
        return IEditor::instance();
    }

    static void destroy();

    QHash<int, IAggregate*> _aggregates;
    int _isInCommand : 1;
    int _isCreating : 1;

protected:
    Editor();
    virtual IAggregator *init();
    virtual ~Editor();

    // IEditor
    bool isInCommand() const
    {
        return _isInCommand;
    }

    void beginCommand()
    {
        _isInCommand = true;
    }

    void endCommand()
    {
        _isInCommand = false;
    }

    void pushCommand(QUndoCommand *command)
    {
    }

    bool isCreating() const
    {
        return false;
    }

    void startCreating()
    {
        _isCreating = true;
    }

    void finishCreating()
    {
        _isCreating = false;
    }

    // IAggregator
    QList<IAggregate*> aggregates() const
    {
        return _aggregates.values();
    }

    IAggregate *appendAggregate(IAggregate *aggregate);
    void removeAggregate(IAggregate *aggregate);
    void clear();

public:
    // IUnknown
    void *queryInterface(int interfaceType)
    {
        if (I::IAggregator == interfaceType)
            return this;
        IAggregate *interface = _aggregates.value(interfaceType);
        if (interface)
            return interface;
        return createAggregate(interfaceType);
    }

    const void *queryInterface(int interfaceType) const
    {
        if (I::IAggregator == interfaceType)
            return this;
        IAggregate *interface = _aggregates.value(interfaceType);
        if (interface)
            return interface;
        return 0;
    }
};

} // namespace Gui
} // namespace Mi

#endif // MI_GUI_EDITOR_H
