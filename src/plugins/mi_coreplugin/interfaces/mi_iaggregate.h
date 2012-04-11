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

#ifndef MI_IAGGREGATE_H
#define MI_IAGGREGATE_H

#include "mi_iunknown.h"

#include <mi_iaggregator.h>

class IAggregate : public IUnknown
{
public:
    Q_I_BASE__UNKNOWN__INTERFACE_TYPE(IAggregate)

    virtual IAggregator *aggregator() const = 0;

    const void *queryInterface(int interfaceType) const
    {
        if (isTypeOfInterface(interfaceType))
            return this;
        return aggregator()->queryInterface(interfaceType);
    }
};

#endif // MI_IAGGREGATE_H
