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

#ifndef IGRAPHICSDATA_H
#define IGRAPHICSDATA_H

#include <icomponent.h>
#include "ac_gui_interfaces.h"

class QGraphicsItem;
class QVariant;

class IGraphicsData : public IComponent
{
public:
    enum { InterfaceType = I::IGraphicsData };

    virtual QGraphicsItem *node(int sceneType, int transformType) const = 0;
    virtual void update(int role, const QVariant &value) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType ? true : IComponent::isTypeOfInterface(interfaceType);
    }
};

#endif
