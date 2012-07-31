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

#include "mi_core_session_classfactory.h"

#include "mi_iaggregate.h"

#include "mi_core_session_aggregate.h"

static IClassFactory *instance = 0;

IClassFactory *IClassFactory::instance()
{
    return ::instance;
}

namespace Mi {
namespace Core {
namespace Session {

ClassFactory::ClassFactory(IAggregate *aggregate)
    :   _aggregate(static_cast<Aggregate*>(aggregate))
{
    Q_ASSERT(dynamic_cast<Aggregate*>(aggregate));
    ::instance = this;
}

ClassFactory::~ClassFactory()
{
    ::instance = 0;
}

IUnknown *ClassFactory::initialize()
{
    aggregate()->append(this);
    return this;
}

void *ClassFactory::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ClassFactory*>(this);
    return aggregate()->queryInterface(interfaceType);
}

}
}
}
