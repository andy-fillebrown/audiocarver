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

#ifndef MI_CORE_SESSION_CLASSFACTORY_H
#define MI_CORE_SESSION_CLASSFACTORY_H

#include "mi_iclassfactory.h"

class IAggregate;

namespace Mi {
namespace Core {
namespace Session {

class Aggregate;

class MI_CORE_EXPORT ClassFactory : public IClassFactory
{
    friend class Aggregate;

    Aggregate *_aggregate;

protected:
    ClassFactory(IAggregate *aggregate);
    ~ClassFactory();
    virtual IUnknown *initialize();

    Aggregate *aggregate() const
    {
        return _aggregate;
    }

    void *queryInterface(int interfaceType) const;
};

}
}
}

#endif
