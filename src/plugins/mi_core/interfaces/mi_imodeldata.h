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

#ifndef MI_IMODELDATA_H
#define MI_IMODELDATA_H

#include "mi_iunknown.h"

class IModelData : public IUnknown
{
public:
    enum { InterfaceType = I::IModelData };

    virtual int roleCount() const = 0;
    virtual int roleAt(int i) const = 0;
    virtual QVariant getValue(int role) const = 0;
    virtual bool setValue(const QVariant &value, int role) = 0;
    virtual Qt::ItemFlags flags() const = 0;

    template <typename T> T get(int role) const
    {
        return getValue(role).value<T>();
    }

    bool set(const QVariant &value, int role)
    {
        return setValue(value, role);
    }

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif // MI_IMODELDATA_H
