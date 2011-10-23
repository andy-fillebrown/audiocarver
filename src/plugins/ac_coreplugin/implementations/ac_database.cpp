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

#include <ac_score.h>
#include <ac_xmlfiler.h>

class DatabasePrivate
{
public:
    Database *q;
    XmlFileReader reader;

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

QString Database::fileName() const
{
    return d->reader.fileName();
}

void Database::reset()
{
    Score::instance()->clear();
}

void Database::read(const QString &fileName)
{
    reset();
    d->reader.setFileName(fileName);
    d->reader.read(query<IModelItem>(Score::instance()));
    d->reader.close();
}

void Database::write(const QString &fileName)
{
    XmlFileWriter writer;
    writer.setFileName(fileName);
    writer.write(query<IModelItem>(Score::instance()));
}
