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

#ifndef IDATAOBJECT_H
#define IDATAOBJECT_H

#include "iobject.h"

namespace Database {

class IDataList;
class IListObject;

class IDataObject : public IObject
{
    Q_OBJECT

public:
    IDataObject() {}
    virtual ~IDataObject() {}

    virtual QString uniqueName() const = 0;
};

} // namespace Database

#endif // IDATAOBJECT_H
