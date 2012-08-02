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

#include "mi_core_base_classfactory.h"
#include "mi_core_iaggregate.h"
#include "mi_core_isession.h"

static IClassFactory *instance = 0;

IClassFactory *IClassFactory::instance()
{
    return ::instance;
}

namespace Base {

ClassFactory::ClassFactory()
{
    ISession::instance()->remove(IClassFactory::instance());
    ::instance = this;
}

ClassFactory::~ClassFactory()
{
    ::instance = 0;
}

IUnknown *ClassFactory::initialize()
{
    ISession::instance()->append(this);
    return this;
}

void *ClassFactory::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ClassFactory*>(this);
    return ISession::instance()->queryInterface(interfaceType);
}

}
