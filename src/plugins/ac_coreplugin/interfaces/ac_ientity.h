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

#include <mi_iunknown.h>

#include <ac_point.h>

class IEntity : public IUnknown
{
public:
    virtual bool isSubEntity() const = 0;
    virtual PointList points() const = 0;
    virtual void setPoints(const PointList &points) = 0;
    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
};

#endif // AC_IENTITY_H
