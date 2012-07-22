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

#ifndef MI_CORE_ROOT_H
#define MI_CORE_ROOT_H

#include "mi_core_qaggregator.h"

#include <mi_iorphanage.h>

namespace Mi {

class CorePlugin;

namespace Core {

class MI_CORE_EXPORT Root : public QAggregator
{
    friend class Mi::CorePlugin;
    friend class Orphanage;

    QList<IAggregator*> _orphans;

protected:
    static Root *instance();

    Root();
    virtual ~Root();
    IAggregator *init();

    QList<IAggregator*> &orphans()
    {
        return _orphans;
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_ROOT_H
