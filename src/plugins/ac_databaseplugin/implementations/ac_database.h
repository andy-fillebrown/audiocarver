/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include <mi_idatabase.h>

namespace Private {

class AcDatabaseImplData;

class AcDatabaseImpl : public MiIDatabase
{
public:
    AcDatabaseImpl();
private:
    ~AcDatabaseImpl();
    Q_DISABLE_COPY(AcDatabaseImpl)

private:
    const QString &fileExtension() const;
    const QString &fileFilter() const;

    const QString &fileName() const;

    void clear();
    void read(const QString &fileName);
    void write(const QString &fileName);

private:
    AcDatabaseImplData *d;
};

} // namespace Private

#endif // AC_DATABASE_H
