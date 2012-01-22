/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include <ac_ifactory.h>
#include <ac_ifiler.h>
#include <ac_model.h>
#include <ac_score.h>

class DatabasePrivate
{
public:
    Database *q;
    QString fileName;
    quint32 reading : 32;

    DatabasePrivate(Database *q)
        :   q(q)
        ,   reading(quint32(false))
    {}

    virtual ~DatabasePrivate()
    {}
};

Database::Database()
    :   d(new DatabasePrivate(this))
{}

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
    return d->fileName;
}

void Database::reset()
{
    Score::instance()->clear();
    d->fileName.clear();
    emit databaseReset();
}

void Database::read(const QString &fileName)
{
    emit databaseAboutToBeRead();
    d->reading = true;
    reset();
    IReader *reader = IFilerFactory::instance()->createReader(Ac::XmlFileFiler);
    query<IFileFiler>(reader)->setFileName(fileName);
    reader->read(query<IModelItem>(Score::instance()));
    delete reader;
    d->reading = false;
    d->fileName = fileName;
    emit databaseRead();
}

void Database::write(const QString &fileName)
{
    emit databaseAboutToBeWritten();
    IWriter *writer = IFilerFactory::instance()->createWriter(Ac::XmlFileFiler);
    query<IFileFiler>(writer)->setFileName(fileName);
    writer->write(query<IModelItem>(Score::instance()));
    delete writer;
    d->fileName = fileName;
    emit databaseWritten();
}

bool Database::isReading() const
{
    return d->reading;
}
