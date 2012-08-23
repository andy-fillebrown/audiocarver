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

#include "filerfactory.h"
#include <interfaces/iaggregate.h>
#include <interfaces/isession.h>

static IFilerFactory *instance = 0;

IFilerFactory *IFilerFactory::instance()
{
    return ::instance;
}

namespace Base {

FilerFactory::FilerFactory()
{
    ISession::instance()->remove(::instance);
    delete ::instance;
    ::instance = this;
}

FilerFactory::~FilerFactory()
{
    ::instance = 0;
}

IUnknown *FilerFactory::initialize()
{
    return ISession::instance()->append(this);
}

void *FilerFactory::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<FilerFactory*>(this);
    return ISession::instance()->queryInterface(interfaceType);
}

}
