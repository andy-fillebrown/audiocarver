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

#include "mi_core_model.h"

#include <mi_core_root.h>

static IModel *instance = 0;

IModel *IModel::instance()
{
    return ::instance;
}

namespace Mi {
namespace Core {

Model::Model(Root *aggregator)
    :   IModel(aggregator)
{
    ::instance = this;
}

IAggregate *Model::init()
{
    return this;
}

Model::~Model()
{
    ::instance = 0;
}

} // namespace Core
} // namespace Mi
