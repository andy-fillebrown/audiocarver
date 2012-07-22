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

#ifndef MI_CORE_QAGGREGATOR_H
#define MI_CORE_QAGGREGATOR_H

#include "mi_core_aggregator.h"

namespace Mi {
namespace Core {

class MI_CORE_EXPORT QAggregator : public Aggregator
{
    QHash<int, QObject*> _qobjects;

protected:
    QAggregator()
    {}

    ~QAggregator();

    virtual QObject *createQObject(int interfaceType)
    {
        return 0;
    }

    virtual QObject *appendQObject(int interfaceType, QObject *qobject)
    {
        if (!_qobjects.contains(interfaceType))
            _qobjects.insert(interfaceType, qobject);
        return qobject;
    }

    void clear();

public:
    // IUnknown
    void *queryInterface(int interfaceType)
    {
        void *interface = Aggregator::queryInterface(interfaceType);
        if (interface)
            return interface;
        interface = _qobjects.value(interfaceType);
        if (interface)
            return interface;
        return createQObject(interfaceType);
    }

    const void *queryInterface(int interfaceType) const
    {
        const void *interface = Aggregator::queryInterface(interfaceType);
        if (interface)
            return interface;
        interface = _qobjects.value(interfaceType);
        if (interface)
            return interface;
        return 0;
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_AGGREGATOR_H
