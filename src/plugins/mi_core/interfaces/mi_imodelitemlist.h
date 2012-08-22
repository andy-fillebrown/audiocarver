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

#ifndef MI_IMODELITEMLIST_H
#define MI_IMODELITEMLIST_H

#include "mi_imodelitem.h"

class QString;

class IModelItemList : public IModelItem
{
public:
    enum { InterfaceType = I::IModelItemList };

    bool isList() const
    {
        return true;
    }

    virtual int listType() const = 0;
    virtual bool contains(const QString &name) const = 0;
    virtual void insert(int i, IModelItem *item) = 0;
    virtual void removeAt(int i) = 0;

    bool isEmpty() const
    {
        return count() == 0;
    }

    void append(IModelItem *item)
    {
        insert(count(), item);
    }

    IModelItem *takeAt(int i)
    {
        IModelItem *item = at(i);
        removeAt(i);
        return item;
    }

    void remove(IModelItem *item)
    {
        removeAt(indexOf(item));
    }

    void removeLast()
    {
        removeAt(count() - 1);
    }

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

#endif
