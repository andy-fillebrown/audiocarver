/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#ifndef AC_IENTITY_H
#define AC_IENTITY_H

#include <ac_point.h>

#include <mi_iunknown.h>

class IEntity : public IUnknown
{
public:
    enum { Type = Ac::EntityInterface };

    virtual PointList points() const = 0;
    virtual void setPoints(const PointList &points, Ac::DragState dragState = Ac::NotDragging) = 0;
    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
};

class ISubEntity : public IUnknown
{
public:
    enum { Type = Ac::SubEntityInterface };

    virtual IEntity *parentEntity() const = 0;
};

#endif // AC_IENTITY_H
