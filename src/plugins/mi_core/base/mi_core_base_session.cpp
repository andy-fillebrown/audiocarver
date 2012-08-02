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

#include "mi_core_base_session.h"
#include "mi_core_isession.h"

static IAggregate *instance = 0;

IAggregate *ISession::instance()
{
    return ::instance;
}

namespace Base {

Session::Session()
{
    delete ::instance;
    ::instance = this;
}

IAggregate *Session::initialize()
{
    return this;
}

Session::~Session()
{
    ::instance = 0;
}

}
