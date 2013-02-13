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

#ifndef IGRAPHICSENTITY_H
#define IGRAPHICSENTITY_H

#include <igraphicsitem.h>
#include "ac_gui_interfaces.h"

class IGraphicsEntity : public IGraphicsItem
{
public:
    enum { InterfaceType = I::IGraphicsEntity };

//    virtual void setColor(int color) = 0;
    virtual void setColor(int color)
    {
        Q_ASSERT(false);
    }

    virtual void highlight(bool on = true) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IGraphicsItem::isTypeOfInterface(interfaceType);
    }
};

#endif
