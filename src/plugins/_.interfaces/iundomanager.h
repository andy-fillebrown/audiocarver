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

#ifndef IUNDOMANAGER_H
#define IUNDOMANAGER_H

#include <icomponent.h>
#include <iaggregate.h>
#include <isession.h>

class IUndoManager : public IComponent
{
public:
    enum { InterfaceType = I::IUndoManager };

    inline static IUndoManager *instance()
    {
        return query<IUndoManager>(ISession::instance());
    }

    virtual bool isUndoing() const = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual bool isPaused() const = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual bool isInCommand() const = 0;
    virtual void beginCommand() = 0;
    virtual void endCommand() = 0;
    virtual void pushCommand(int commandId) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IComponent::isTypeOfInterface(interfaceType);
    }
};

#endif
