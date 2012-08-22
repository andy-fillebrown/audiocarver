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

#ifndef MI_SESSION_H
#define MI_SESSION_H

#include "mi_aggregate.h"

namespace Mi {
namespace Core {
    class Plugin;
}
}

namespace Base {

class MI_CORE_EXPORT Session : public Aggregate
{
    friend class Mi::Core::Plugin;

protected:
    Session();
    virtual ~Session();
    IAggregate *initialize();

    void clear()
    {}
};

}

#endif
