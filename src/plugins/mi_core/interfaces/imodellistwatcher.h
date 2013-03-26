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

#ifndef IMODELLISTWATCHER_H
#define IMODELLISTWATCHER_H

#include <icomponent.h>

class IModelItem;

class IModelListWatcher : public IComponent
{
public:
    enum { InterfaceType = I::IModelListWatcher };

    virtual void beginInsertItem(const IModelItem *list, int index) = 0;
    virtual void endInsertItem(const IModelItem *list, int index) = 0;
    virtual void beginRemoveItem(const IModelItem *list, int index) = 0;
    virtual void endRemoveItem(const IModelItem *list, int index) = 0;

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
