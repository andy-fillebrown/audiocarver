/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "mi_core_common_modelitem.h"
#include "mi_core_common_aggregate.h"
#include "mi_core_namespace.h"
#include "mi_core_scopedparentchange.h"
#include <iaggregate.h>

using namespace Mi;

namespace Common {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

IModelItem *ModelItem::parent() const
{
    IAggregate *parent_aggregate = aggregate()->parent();
    if (parent_aggregate)
        return query<IModelItem>(parent_aggregate);
    return 0;
}

}
