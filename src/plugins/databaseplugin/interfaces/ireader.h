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

#ifndef IREADER_H
#define IREADER_H

#include "ifiler.h"

namespace Database {

class IReader : public IFiler
{
    Q_OBJECT

public:
    IReader();
    virtual ~IReader();

    virtual void readDataList(IDataList *list) = 0;
    virtual void readDataObject(IDataObject *object) = 0;

    virtual void readLinkList(ILinkList *list) = 0;
    virtual void readLinkObject(ILinkObject *object) = 0;
};

} // namespace Database

#endif // IREADER_H
