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

#ifndef IGRAPHICSITEM_H
#define IGRAPHICSITEM_H

#include <iunknown.h>
#include "ac_gui_interfaces.h"
#include <ac_core_point.h>

class QGraphicsItem;
class QRectF;

class IGraphicsItem : public IUnknown
{
public:
    enum { InterfaceType = I::IGraphicsItem };

    virtual QGraphicsItem *graphicsItem(int sceneType, int transformType) const = 0;
    virtual void setPoints(const PointList &points) = 0;
    virtual bool intersects(const QRectF &rect) const = 0;
    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
    virtual bool isVisible() const = 0;

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
