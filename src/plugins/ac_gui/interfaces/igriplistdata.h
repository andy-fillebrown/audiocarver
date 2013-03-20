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

#ifndef IGRIPLISTDATA_H
#define IGRIPLISTDATA_H

#include <igraphicssubentitydata.h>
#include "ac_gui_interfaces.h"
#include <QList>

class IGripData;

class IGripListData : public IGraphicsSubEntityData
{
public:
    enum { InterfaceType = I::IGripListData };

    virtual QList<IGripData*> grips() const = 0;
    virtual void sort() = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IGraphicsSubEntityData::isTypeOfInterface(interfaceType);
    }
};

#endif
