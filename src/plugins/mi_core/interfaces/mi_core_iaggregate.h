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

#ifndef MI_CORE_IAGGREGATE_H
#define MI_CORE_IAGGREGATE_H

#include "mi_core_interfaces.h"
#include "mi_core_iunknown.h"

template <typename T> class QList;

class IAggregate : public IUnknown
{
public:
    enum { InterfaceType = I::IAggregate };

    virtual const QList<IUnknown*> &components() const = 0;
    virtual IUnknown *append(IUnknown *component) = 0;
    virtual void remove(IUnknown *component) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }

    void *queryInterface(int interfaceType) const
    {
        if (isTypeOfInterface(interfaceType))
            return const_cast<IAggregate*>(this);
        return 0;
    }
};

#endif
