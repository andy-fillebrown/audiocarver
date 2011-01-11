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

#ifndef AC_DATABASE_H
#define AC_DATABASE_H

#include <databaseplugin/interfaces/idatabase.h>

namespace AudioCarver {
namespace Internal {

class DatabaseImpl : public Database::IDatabase
{
public:
    DatabaseImpl();
    virtual ~DatabaseImpl();

    virtual const QString &fileExtension() const;
    virtual const QString &fileFilter() const;

    virtual const QString &fileName() const;

    virtual void clear();
    virtual void read(const QString &fileName);
    virtual void write(const QString &fileName);
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_DATABASE_H
