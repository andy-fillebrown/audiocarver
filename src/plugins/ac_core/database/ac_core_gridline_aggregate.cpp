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

#include "ac_core_gridline_aggregate.h"
#include "ac_core_constants.h"

namespace GridLine {

Aggregate::Aggregate(IAggregate *parent)
    :   Object::Aggregate(parent)
    ,   location(Q_FLOAT_MIN)
    ,   priority(0)
    ,   color(DEFAULT_GRIDLINE_COLOR)
    ,   visible(true)
{}

}
