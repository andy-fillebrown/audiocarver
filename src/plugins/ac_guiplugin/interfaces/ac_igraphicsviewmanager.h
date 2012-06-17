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

#ifndef AC_IGRAPHICSVIEWMANAGER_H
#define AC_IGRAPHICSVIEWMANAGER_H

#include "mi_iaggregate.h"

#include <ac_guinamespace.h>

class IGraphicsViewGroup;

class ISceneManager : public IAggregate
{
public:
    enum { InterfaceType = I::IGraphicsViewManager };

    virtual int count() const = 0;
    virtual IGraphicsViewGroup *at(int i) const = 0;
    virtual void append(IGraphicsViewGroup *group) = 0;
    virtual void remove(IGraphicsViewGroup *group) = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IAggregate::isTypeOfInterface(interfaceType);
    }
};

#endif // AC_IGRAPHICSVIEWMANAGER_H
