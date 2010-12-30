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

#ifndef ILINKOBJECT_H
#define ILINKOBJECT_H

#include "iobject.h"

namespace Database {

class IDataObject;
class ILinkList;

class ILinkObject : public IObject
{
    Q_OBJECT

public:
    ILinkObject() {}
    virtual ~ILinkObject() {}

    virtual ILinkList *parent() const = 0;

    virtual IDataObject *dataObject() const = 0;
    virtual void setDataObject(IDataObject *object) = 0;
};

} // namespace Database

#endif // ILINKOBJECT_H
