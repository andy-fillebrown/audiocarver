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

#ifndef AC_IENTITY_H
#define AC_IENTITY_H

#include "mi_iaggregate.h"

#include <ac_guinamespace.h>

class IEntity : public IAggregate
{
public:
    Q_IUNKNOWN_DERIVED__INTERFACETYPE(IEntity, IAggregate)

    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
    virtual bool intersects(const QRectF &rect) const = 0;
    virtual bool isVisible() const = 0;
};

#endif // AC_IENTITY_H
