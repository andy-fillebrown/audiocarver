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

#ifndef IEDITOR_H
#define IEDITOR_H

#include <icomponent.h>
#include <iaggregate.h>
#include <isession.h>

class ISelectionSet;

class IEditor : public IComponent
{
public:
    enum { InterfaceType = I::IEditor };

    inline static IEditor *instance()
    {
        return query<IEditor>(ISession::instance());
    }

    virtual ISelectionSet *currentSelection(int itemType = 0) const = 0;
    virtual void cut() = 0;
    virtual void copy() const = 0;
    virtual void paste() = 0;
    virtual void selectAll() = 0;

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