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

#ifndef MI_IMODELITEMWATCHER_H
#define MI_IMODELITEMWATCHER_H

#include "mi_iunknown.h"

class IModelItem;

class IModelItemWatcher : public IUnknown
{
public:
    enum { InterfaceType = I::IModelItemWatcher };

    virtual void beginChangeParent(const IModelItem *item) = 0;
    virtual void endChangeParent(const IModelItem *item) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif // MI_IMODELITEMWATCHER_H