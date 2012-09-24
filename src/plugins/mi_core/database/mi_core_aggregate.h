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

#ifndef MI_CORE_AGGREGATE_H
#define MI_CORE_AGGREGATE_H

#include <iaggregate.h>
#include "mi_core_global.h"
#include <QList>

namespace Base {

class MI_CORE_EXPORT Aggregate : public IAggregate
{
    QList<IUnknown*> _components;

public:
    Aggregate();
    ~Aggregate();
    virtual IAggregate *initialize();
    void *queryInterface(int interfaceType) const;

protected:
    const QList<IUnknown*> &components() const
    {
        return _components;
    }

    IUnknown *append(IUnknown *component)
    {
        if (!_components.contains(component))
            _components.append(component);
        return component;
    }

    void remove(IUnknown *component)
    {
        _components.removeOne(component);
    }
};

}

#endif
