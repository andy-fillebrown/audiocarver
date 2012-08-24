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

#ifndef IGRAPHICSVIEWMANAGER_H
#define IGRAPHICSVIEWMANAGER_H

#include <iunknown.h>
#include "ac_gui_interfaces.h"

class IGraphicsViewGroup;

class IGraphicsViewManager : public IUnknown
{
public:
    enum { InterfaceType = I::IGraphicsViewManager };

    virtual int count() const = 0;
    virtual IGraphicsViewGroup *at(int i) const = 0;
    virtual void append(IGraphicsViewGroup *group) = 0;
    virtual void remove(IGraphicsViewGroup *group) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif