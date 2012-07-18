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

#ifndef AC_IGRAPHICSSCENE_H
#define AC_IGRAPHICSSCENE_H

#include "mi_iaggregate.h"

#include <ac_gui_namespace.h>

class IGraphicsItem;

class IGraphicsScene : public IAggregate
{
public:
    enum { InterfaceType = I::IGraphicsScene };

    virtual int sceneType() const = 0;
    virtual void appendItem(IGraphicsItem *item) = 0;
    virtual void removeItem(IGraphicsItem *item) = 0;

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

#endif // AC_IGRAPHICSSCENE_H
