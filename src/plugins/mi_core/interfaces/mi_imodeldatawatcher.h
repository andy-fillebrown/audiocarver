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

#ifndef MI_IMODELDATAWATCHER_H
#define MI_IMODELDATAWATCHER_H

#include "mi_iunknown.h"
#include "mi_core_interfaces.h"

class IModelData;

class IModelDataWatcher : public IUnknown
{
public:
    enum { InterfaceType = I::IModelDataWatcher };

    virtual void beginChangeData(const IModelData *data, int role, int dataChangeType) = 0;
    virtual void endChangeData(const IModelData *data, int role, int dataChangeType) = 0;

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
