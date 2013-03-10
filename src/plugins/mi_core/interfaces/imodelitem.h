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

class IModelItemList;

class IModelItem : public IComponent
{
public:
    enum { InterfaceType = I::IModelItem };

    virtual bool isList() const
    {
        return false;
    }

    virtual IModelItem *parent() const = 0;
    virtual void setParent(IModelItem *parent) = 0;
    virtual IModelItemList *list() const = 0;
    virtual int count() const = 0;
    virtual int indexOf(const IModelItem *item) const = 0;
    virtual IModelItem *at(int i) const = 0;
    virtual IModelItem *findItem(int itemType) const = 0;
    virtual IModelItemList *findList(int listType) const = 0;
    virtual void reset() = 0;

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

#endif
