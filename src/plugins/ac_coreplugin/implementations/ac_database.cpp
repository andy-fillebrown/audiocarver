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

#include <ac_ifactory.h>
#include <ac_ifiler.h>
#include <ac_model.h>
#include <ac_score.h>

class DatabasePrivate
{
public:
    Database *q;
    IReader *reader;
    quint32 reading : 32;

    DatabasePrivate(Database *q)
        :   q(q)
        ,   reader(IFilerFactory::instance()->createReader(Ac::XmlFileFiler))
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
    return query<IFileFiler>(d->reader)->fileName();
}

void Database::reset()
{
    Score::instance()->clear();
}

void Database::read(const QString &fileName)
{
    emit databaseAboutToBeRead();
    d->reading = quint32(true);
    reset();
    IFileFiler *fileFiler = query<IFileFiler>(d->reader);
    fileFiler->setFileName(fileName);
    d->reader->read(query<IModelItem>(Score::instance()));
    fileFiler->close();
    d->reading = quint32(false);
    emit databaseRead();
}

void Database::write(const QString &fileName)
{
    emit databaseAboutToBeWritten();
    IWriter *writer = IFilerFactory::instance()->createWriter(Ac::XmlFileFiler);
    query<IFileFiler>(writer)->setFileName(fileName);
    writer->write(query<IModelItem>(Score::instance()));
    delete writer;
    emit databaseWritten();
}

bool Database::isReading() const
{
    return d->reading;
}
