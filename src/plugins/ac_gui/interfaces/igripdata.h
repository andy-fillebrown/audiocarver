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

#ifndef IGRIPDATA_H
#define IGRIPDATA_H

#include <igraphicssubentitydata.h>
#include "ac_gui_interfaces.h"

class QPointF;

class IGripData : public IGraphicsSubEntityData
{
public:
    enum { InterfaceType = I::IGripData };

    virtual QPointF originalPosition() const = 0;
    virtual QPointF position() const = 0;
    virtual int curveType() const = 0;

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
