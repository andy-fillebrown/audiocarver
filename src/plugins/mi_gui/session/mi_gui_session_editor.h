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

#ifndef MI_GUI_SESSION_EDITOR_H
#define MI_GUI_SESSION_EDITOR_H

#include "mi_gui_ieditor.h"

namespace Session {

class MI_GUI_EXPORT Editor : public IEditor
{
    int _isInCommand : 1;
    int _isCreating : 1;

public:
    Editor();
    virtual IUnknown *initialize();
    virtual ~Editor();
    void *queryInterface(int interfaceType) const;

protected:
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
};

}

#endif
