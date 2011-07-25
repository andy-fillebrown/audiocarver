/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#ifndef MI_ICOMPONENT_H
#define MI_ICOMPONENT_H

#include <aggregate.h>
#include <mi_core_global.h>
#include <QObject>

namespace Database {

class IComponent : protected QObject
{
    Q_OBJECT

public:
    template <typename T>
    T *query() const
    {
        return Aggregation::query<T>(const_cast<IComponent*>(this));
    }

private:
    Q_DISABLE_COPY(IComponent)
    Q_ENABLE_QUERY(IComponent)
    friend class IParent;
    friend class Object;
};

} // namespace Database

#endif // MI_ICOMPONENT_H
