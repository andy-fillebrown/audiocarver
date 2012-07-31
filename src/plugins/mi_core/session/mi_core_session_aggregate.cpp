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

#include "mi_core_session_aggregate.h"

#include "mi_isession.h"

static Mi::Core::Session::Aggregate *instance = 0;

IAggregate *ISession::instance()
{
    return ::instance;
}

namespace Mi {
namespace Core {
namespace Session {

Aggregate::Aggregate()
{
    delete ::instance;
    ::instance = this;
}

IAggregate *Aggregate::initialize()
{
    return this;
}

Aggregate::~Aggregate()
{
    ::instance = 0;
}

}
}
}
