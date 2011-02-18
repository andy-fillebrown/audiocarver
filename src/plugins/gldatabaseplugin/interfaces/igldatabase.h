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

#ifndef IGLDATABASE_H
#define IGLDATABASE_H

#include <gldatabaseplugin/gldatabase_global.h>

#include <databaseplugin/interfaces/idatabase.h>

namespace GLDatabase {

class IGLModel;

class GLDATABASE_EXPORT IGLDatabase : public Database::IDatabase
{
    Q_OBJECT

public:
    IGLDatabase();
    virtual ~IGLDatabase();

    virtual IGLModel *model() const = 0;
};

} // namespace GLDatabase

#endif // IGLDATABASE_H
