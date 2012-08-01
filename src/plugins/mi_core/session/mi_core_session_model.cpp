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

#include "mi_core_session_model.h"

#include "mi_iaggregate.h"

static IModel *instance = 0;

IModel *IModel::instance()
{
    return ::instance;
}

namespace Mi {
namespace Core {
namespace Session {

Model::Model(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    ::instance = this;
}

Model::~Model()
{
    ::instance = 0;
}

IUnknown *Model::initialize()
{
    aggregate()->append(this);
    return this;
}

void *Model::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<Model*>(this);
    return aggregate()->queryInterface(interfaceType);
}

}
}
}
