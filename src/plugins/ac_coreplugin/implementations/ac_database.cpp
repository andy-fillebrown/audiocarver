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

#include "ac_database.h"

class DatabasePrivate
{
public:
    Database *q;
    QString fileName;

    DatabasePrivate(Database *q)
        :   q(q)
    {}

    virtual ~DatabasePrivate()
    {}
};

Database::Database()
    :   d(new DatabasePrivate(this))
{}

Database::~Database()
{
    delete d;
}

const QString &Database::fileExtension() const
{
    static QString ext = QString::fromLatin1(".ac");
    return ext;
}

const QString &Database::fileFilter() const
{
    static QString filter = QString::fromLatin1("AudioCarver (*%1)").arg(fileExtension());
    return filter;
}

const QString &Database::fileName() const
{
    return d->fileName;
}

void Database::clear()
{}

void Database::read(const QString &fileName)
{
    Q_UNUSED(fileName);
}

void Database::write(const QString &fileName)
{
    Q_UNUSED(fileName);
}
