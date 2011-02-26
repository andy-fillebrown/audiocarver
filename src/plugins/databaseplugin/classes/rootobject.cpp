/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "rootobject.h"

using namespace Database;
using namespace Database::Internal;

namespace Database {
namespace Internal {

class RootObjectPrivate
{
public:
    RootObject *q;

    RootObjectPrivate(RootObject *q)
        :   q(q)
    {
    }

    ~RootObjectPrivate()
    {
        q = 0;
    }
};

} // namespace Internal
} // namespace Database

RootObject::RootObject(QObject *parent)
    :   BaseClassT(parent)
    ,   d(new RootObjectPrivate(this))
{
    Q_CHECK_PTR(d);
}

RootObject::~RootObject()
{
    delete d;  d = 0;
}
