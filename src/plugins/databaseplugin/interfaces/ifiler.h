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

#ifndef IFILER_H
#define IFILER_H

#include "../database_global.h"

#include <QtCore/QObject>

namespace Database {

class IDatabase;
class IObject;
class ILinkObject;

class DATABASE_EXPORT IFiler : public QObject
{
    Q_OBJECT

public:
    IFiler() {}
    virtual ~IFiler() {}

    virtual IDatabase *database() const = 0;
};

} // namespace Database

#endif // IFILER_H
