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

#ifndef ISUBENTITYITEM_H
#define ISUBENTITYITEM_H

#include <ichildentity.h>

class IGrip;
class IParentEntity;

class ISubEntity : public IChildEntity
{
public:
    enum { InterfaceType = I::ISubEntity };

    virtual int sceneType() const = 0;
    virtual bool isCurve() const = 0;
    virtual bool intersects(const QRectF &rect) const = 0;
    virtual void startUpdatingPoints() = 0;
    virtual void updatePoints() = 0;
    virtual void finishUpdatingPoints() = 0;
    virtual void updateCurveTypes() = 0;
    virtual QList<IGrip*> grips() const = 0;
    virtual void resetGrips() = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IChildEntity::isTypeOfInterface(interfaceType);
    }
};

#endif
