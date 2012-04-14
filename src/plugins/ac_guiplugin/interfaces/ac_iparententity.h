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

#ifndef AC_IPARENTENTITY_H
#define AC_IPARENTENTITY_H

#include "ac_ientity.h"

class IPoints;
class ISubEntity;

class IParentEntity : public IEntity
{
public:
    Q_IUNKNOWN_DERIVED__INTERFACETYPE(IParentEntity, IEntity)

    virtual QList<ISubEntity*> subEntities(int sceneType) const = 0;
    virtual QList<IPoints*> subEntityPoints(int sceneType) const = 0;
};

#endif // AC_IPARENTENTITY_H
