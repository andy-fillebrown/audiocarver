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

#ifndef MI_IMODELLIST_H
#define MI_IMODELLIST_H

#include "mi_imodelitem.h"

class IModelList : public IModelItem
{
public:
    enum { InterfaceType = I::IModelList };

    virtual int listType() const = 0;
    virtual bool containsItemNamed(const QString &name) const = 0;
    virtual void insertItem(int i, IModelItem *item) = 0;
    virtual void removeItemAt(int i) = 0;
    virtual void clearItems() = 0;

    bool hasItems() const
    {
        return itemCount() != 0;
    }

    void appendItem(IModelItem *item)
    {
        insert(itemCount(), item);
    }

    IModelItem *takeItemAt(int i)
    {
        IModelItem *item = itemAt(i);
        removeItemAt(i);
        return item;
    }

    void removeItem(IModelItem *item)
    {
        removeItemAt(indexOfItem(item));
    }

    void removeLastItem()
    {
        removeItemAt(count() - 1);
    }

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IModelItem::isTypeOfInterface(interfaceType);
    }
};

#endif // MI_IMODELLIST_H
