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

#ifndef IDATALIST_H
#define IDATALIST_H

#include "iobject.h"

namespace Database {

class IDataObject;

class IDataList : public IObject
{
    Q_OBJECT

public:
    IDataList();
    virtual ~IDataList();

    virtual int objectCount() const = 0;
    virtual IDataObject *objectAt(int i) = 0;
    virtual void appendObject(IDataObject *object) = 0;
    virtual void removeObject(IDataObject *object) = 0;
};

} // namespace Database

#endif // IDATALIST_H
