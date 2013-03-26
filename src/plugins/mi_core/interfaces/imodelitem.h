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

#ifndef IMODELITEM_H
#define IMODELITEM_H

#include <icomponent.h>
#include <QVariant>

#define get get
#define qvariant_cast qvariant_cast

class IModelItem : public IComponent
{
public:
    enum { InterfaceType = I::IModelItem };

    virtual int itemType() const = 0;
    virtual bool isTypeOfItem(int itemType) const = 0;
    virtual IModelItem *parent() const = 0;
    virtual void setParent(IModelItem *parent) = 0;
    virtual bool containsItem(IModelItem *item) const = 0;
    virtual bool containsItemNamed(const QString &name) const = 0;
    virtual int itemCount() const = 0;
    virtual int indexOfItem(const IModelItem *item) const = 0;
    virtual IModelItem *itemAt(int i) const = 0;
    virtual IModelItem *findItem(int itemType) const = 0;
    virtual IModelItem *findList(int listType) const = 0;
    virtual void insertItem(int i, IModelItem *item) = 0;
    virtual void removeItemAt(int i) = 0;
    virtual int roleCount() const = 0;
    virtual int roleAt(int i) const = 0;
    virtual QVariant getValue(int role) const = 0;
    virtual bool setValue(const QVariant &value, int role) = 0;
    virtual int flags() const = 0;

    bool isNotEmpty() const
    {
        return itemCount() != 0;
    }

    bool isEmpty() const
    {
        return itemCount() == 0;
    }

    void appendItem(IModelItem *item)
    {
        insertItem(itemCount(), item);
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
        removeItemAt(itemCount() - 1);
    }

    template <typename T> T get_t(int role) const
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
        if (InterfaceType == interfaceType)
            return true;
        return IComponent::isTypeOfInterface(interfaceType);
    }
};

template <typename T>
T get(IModelItem *item, int role)
{
    return item->get_t<T>(role);
}

#endif
