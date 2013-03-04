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

#ifndef ISELECTIONSET_H
#define ISELECTIONSET_H

#include <iunknown.h>
#include "ac_gui_interfaces.h"

class IModelItem;
template <typename T> class QList;

class ISelectionSet : public IUnknown
{
public:
    enum { InterfaceType = I::ISelectionSet };

    virtual const QList<IModelItem*> &items() const = 0;
    virtual bool append(IModelItem *item) = 0;
    virtual bool append(const QList<IModelItem*> &items) = 0;
    virtual bool remove(IModelItem *item) = 0;
    virtual bool remove(const QList<IModelItem*> &items) = 0;
    virtual void clear() = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif
