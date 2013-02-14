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

#ifndef IGRAPHICSCURVE_H
#define IGRAPHICSCURVE_H

#include <igraphicsentity.h>
#include <ac_core_point.h>

class QRectF;

class IGraphicsCurve : public IGraphicsEntity
{
public:
    enum { InterfaceType = I::IGraphicsCurve };

    virtual bool intersects(const QRectF &rect) const = 0;
    virtual void setPoints(const PointList &points) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IGraphicsEntity::isTypeOfInterface(interfaceType);
    }
};

#endif