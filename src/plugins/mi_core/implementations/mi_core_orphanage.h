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

#ifndef MI_ORPHANAGE_H
#define MI_ORPHANAGE_H

#include "mi_iorphanage.h"

class MI_CORE_EXPORT Orphanage : public IOrphanage
{
    friend class MiCorePlugin;

    QList<IAggregator*> _orphans;

    static IOrphanage *instance()
    {
        return IOrphanage::instance();
    }

    static void destroy();

    Orphanage();
    ~Orphanage();

    void append(IAggregator *aggregator);
    void remove(IAggregator *aggregator);
};

#endif // MI_ORPHANAGE_H
