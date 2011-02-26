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

#include "object.h"

using namespace Database;
using namespace Database::Internal;

namespace Database {
namespace Internal {

class ObjectPrivate
{
public:
    Object *q;
    quint64 id;
    bool erased;

    ObjectPrivate(Object *q)
        :   q(q)
        ,   id(0)
        ,   erased(false)
    {
    }

    ~ObjectPrivate()
    {
        erased = true;
        id = 0;
        q = 0;
    }
};

} // namespace Internal
} // namespace Database

Object::Object(QObject *parent)
    :   BaseClassT(parent)
    ,   d(new ObjectPrivate(this))
{
    Q_CHECK_PTR(d);
}

Object::~Object()
{
    delete d;  d = 0;
}
