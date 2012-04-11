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

#ifndef MI_IOBJECT_H
#define MI_IOBJECT_H

#include "mi_iunknown.h"
#include "QObject"

#include <mi_interfacedefinitions.h>
#include <mi_namespace.h>




#include <mi_iaggregator.h>

class Object : public QObject
{
    Q_OBJECT

    IAggregator *_aggregator;

public:
    Object(IAggregator *aggregator)
        :   _aggregator(aggregator)
    {}

    ~Object() {}

    IAggregator *aggregator() const
    {
        return qGetPtrHelper(_aggregator);
    }

    const void *queryInterface(int interfaceType) const
    {
        switch (interfaceType) {
        case I::IObject:
            return this;
        default:
            return aggregator()->queryInterface(interfaceType);
        }
    }
};




class IObject : public Object, public IUnknown
{
public:
    Q_I_BASE__UNKNOWN__INTERFACE_TYPE(IObject)

    virtual const void *queryInterface(int interfaceType) const = 0;
};

#endif // MI_IOBJECT_H
