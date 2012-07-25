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

#ifndef MI_IMODELITEM_H
#define MI_IMODELITEM_H

#include "mi_iunknown.h"

class IModelList;

class IModelItem : public IUnknown
{
public:
    enum { InterfaceType = I::IModelItem };

    virtual int itemType() const = 0;
    virtual bool isTypeOfItem(int itemType) const = 0;
    virtual IModelItem *parent() const = 0;
    virtual void setParent(IModelItem *parent) = 0;
    virtual IModelList *list() const = 0;
    virtual int roleCount() const = 0;
    virtual int roleAt(int i) const = 0;
    virtual QVariant getValue(int role) const = 0;
    virtual bool setValue(const QVariant &value, int role) = 0;
    virtual Qt::ItemFlags itemFlags() const = 0;
    virtual int itemCount() const = 0;
    virtual int indexOfItem(const IModelItem *item) const = 0;
    virtual IModelItem *itemAt(int i) const = 0;
    virtual IModelItem *findItem(int itemType) const = 0;
    virtual IModelList *findList(int listType) const = 0;

    template <typename T> T get(int role) const
    {
        return getValue(role).value<T>();
    }

    bool set(const QVariant &value, int role)
    {
        return setValue(value, role);
    }

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif // MI_IMODELITEM_H
