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

#ifndef MI_CORE_DATABASE_H
#define MI_CORE_DATABASE_H

#include "mi_idatabase.h"

class IAggregate;

namespace Mi {
namespace Core {

class MI_CORE_EXPORT Database : public IDatabase
{
    IAggregate *_aggregate;

protected:
    Database(IAggregate *aggregate);
    ~Database();
    virtual IUnknown *initialize();

    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    void *queryInterface(int interfaceType) const;
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_DATABASE_H
