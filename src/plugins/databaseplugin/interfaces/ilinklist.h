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

#ifndef ILINKLIST_H
#define ILINKLIST_H

#include "iobject.h"

namespace Database {

class IDataObject;
class ILinkObject;

class ILinkList : public IObject
{
    Q_OBJECT

public:
    IDataList();
    virtual ~IDataList();

    virtual IRootObject *root() const { return parent()->root(); }
    virtual IDataObject *parent() const = 0;

    virtual int objectCount() const = 0;
    virtual IDataObject *objectAt(int i) = 0;
    virtual void appendObject(ILinkObject *object) = 0;
    virtual void removeObject(ILinkObject *object) = 0;
};

} // namespace Database

#endif // ILINKLIST_H
