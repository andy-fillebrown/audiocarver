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

#include <QObject>

#include "mi_core_global.h"

class IUnknown;

namespace Mi {
namespace Core {

class MI_CORE_EXPORT Aggregate : public QObject
{
    Q_OBJECT

    QList<IUnknown*> _components;

public:
    Aggregate();
    ~Aggregate();
    virtual QObject *initialize();

    const QList<IUnknown*> &components() const
    {
        return _components;
    }

    void appendComponent(IUnknown *component)
    {
        if (_components.contains(component))
            return;
        _components.append(component);
    }

    virtual void *queryInterface(int interfaceType) const;
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_AGGREGATE_H
