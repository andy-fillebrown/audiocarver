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

#include "mi_core_root.h"

#include <mi_iaggregate.h>

#include <mi_core_model.h>
#include <mi_core_orphanage.h>

static Mi::Core::Root *instance = 0;

namespace Mi {
namespace Core {

Root *Root::instance()
{
    return ::instance;
}

Root::Root()
{
    if (::instance)
        delete ::instance;
    ::instance = this;
}

IAggregator *Root::init()
{
    setAggregate(I::IOrphanage, (new Orphanage(this))->init());
    setAggregate(I::IModel, (new Model(this))->init());
    return QAggregator::init();
}

Root::~Root()
{
    ::instance = 0;
}

} // namespace Core
} // namespace Mi
