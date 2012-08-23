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

#ifndef IGRAPHICSVIEWGROUP_H
#define IGRAPHICSVIEWGROUP_H

#include <iunknown.h>
#include "ac_gui_interfaces.h"

class IGraphicsView;

class IGraphicsViewGroup : public IUnknown
{
public:
    enum { InterfaceType = I::IGraphicsViewGroup };

    virtual IGraphicsView *view(int sceneType) const = 0;
    virtual int count() const = 0;
    virtual IGraphicsView *at(int i) const = 0;
    virtual void appendView(IGraphicsView *view) = 0;
    virtual void removeView(IGraphicsView *view) = 0;

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
