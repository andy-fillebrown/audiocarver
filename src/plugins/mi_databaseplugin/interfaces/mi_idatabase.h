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

#ifndef MI_IDATABASE_H
#define MI_IDATABASE_H

#include <QObject>

#include <mi_database_global.h>

class MI_DATABASE_EXPORT MiIDatabase : public QObject
{
    Q_OBJECT

public:
    MiIDatabase();
    virtual ~MiIDatabase() {}

    static MiIDatabase *instance();

    virtual const QString &fileExtension() const = 0;
    virtual const QString &fileFilter() const = 0;

    virtual const QString &fileName() const = 0;

    virtual void clear() = 0;
    virtual void read(const QString &fileName) = 0;
    virtual void write(const QString &fileName) = 0;

private:
    Q_DISABLE_COPY(MiIDatabase)
};

#endif // MI_IDATABASE_H
