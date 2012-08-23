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

#ifndef IPARENTENTITY_H
#define IPARENTENTITY_H

#include <ientity.h>

class IPoints;
class ISubEntity;
template <typename T> class QList;

class IParentEntity : public IEntity
{
public:
    enum { InterfaceType = I::IParentEntity };

    virtual QList<ISubEntity*> subEntities(int sceneType) const = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IEntity::isTypeOfInterface(interfaceType);
    }
};

#endif
