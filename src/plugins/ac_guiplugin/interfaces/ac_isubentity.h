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

#ifndef AC_ISUBENTITYITEM_H
#define AC_ISUBENTITYITEM_H

#include "mi_iaggregate.h"

class IParentEntity;

class ISubEntity : public IAggregate
{
public:
    Q_IUNKNOWN_DERIVED__INTERFACETYPE(ISubEntity, IAggregate)

    virtual IParentEntity *parentEntity() const = 0;
    virtual bool isCurve() const = 0;
    virtual int sceneType() const = 0;
};

#endif // AC_ISUBENTITYITEM_H
