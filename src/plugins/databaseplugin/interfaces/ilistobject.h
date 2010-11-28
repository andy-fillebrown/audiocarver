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

#ifndef ILISTOBJECT_H
#define ILISTOBJECT_H

#include "iobject.h"

namespace Database {

class IDataObject;

class IListObject : public IObject
{
    Q_OBJECT

public:
    IListObject();
    virtual ~IListObject();

    virtual QList<IDataObject *> dataObjects() const = 0;
};

} // namespace Database

#endif // ILISTOBJECT_H
