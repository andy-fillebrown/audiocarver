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

#ifndef AC_IGRAPHICSVIEW_H
#define AC_IGRAPHICSVIEW_H

#include "mi_iaggregator.h"

#include <ac_guinamespace.h>

class IGraphicsView : public IAggregator
{
public:
    enum { InterfaceType = I::IGraphicsView };

    virtual int sceneType() const = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IAggregator::isTypeOfInterface(interfaceType);
    }
};

#endif // AC_IGRAPHICSVIEW_H
