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

#ifndef MI_CORE_ORPHANAGE_H
#define MI_CORE_ORPHANAGE_H

#include "mi_iorphanage.h"

namespace Mi {

class CorePlugin;

namespace Core {

class Root;

class MI_CORE_EXPORT Orphanage : public IOrphanage
{
    friend class Root;

protected:
    Orphanage(Root *aggregator);
    ~Orphanage();
    IAggregate *init();

    Root *aggregator() const;

    // IOrphanage
    void append(IAggregator *orphan);
    void remove(IAggregator *orphan);
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_ORPHANAGE_H
