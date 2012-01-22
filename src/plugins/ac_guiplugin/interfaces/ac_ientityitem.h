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

#ifndef AC_IENTITYITEM_H
#define AC_IENTITYITEM_H

#include <ac_namespace.h>

#include <mi_iunknown.h>

class IEntity;

class IEntityItem : public IUnknown
{
public:
    enum { Type = Ac::EntityItemInterface };

    virtual IEntity *entity() const = 0;
    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
    virtual void startDraggingPoints() = 0;
    virtual void updatePoints() = 0;
    virtual void finishDraggingPoints() = 0;
};

#endif // AC_IGRIP_H
