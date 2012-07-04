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

#include <ac_corenamespace.h>
#include <ac_factory.h>
#include <ac_model.h>

namespace Ac {

using namespace Database;

IAggregator *Database::init()
{
    _score = query<Factory>(this)->create(Ac::ScoreItem);
    return Mi::Database::init();
}

Database::~Database()
{
    delete _score;
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
    return "";
}

void Database::reset()
{
    score()->clear();
}

void Database::read(const QString &fileName)
{
//    emit databaseAboutToBeRead();
//    d->reading = true;
//    reset();
//    IReader *reader = IFilerFactory::instance()->createReader(Ac::XmlFileFiler);
//    query<IFileFiler>(reader)->setFileName(fileName);
//    reader->read(query<IModelItem>(Score::instance()));
//    delete reader;
//    d->reading = false;
//    d->fileName = fileName;
//    emit databaseRead();
}

void Database::write(const QString &fileName)
{
//    emit databaseAboutToBeWritten();
//    IWriter *writer = IFilerFactory::instance()->createWriter(Ac::XmlFileFiler);
//    query<IFileFiler>(writer)->setFileName(fileName);
//    writer->write(query<IModelItem>(Score::instance()));
//    delete writer;
//    d->fileName = fileName;
//    emit databaseWritten();
}

bool Database::isReading() const
{
//    return d->reading;
    return false;
}


IAggregate *Database::createAggregate(int interfaceType)
{
    switch (interfaceType) {
    case I::IFactory:
        return appendAggregate((new Factory(this))->init());
    case I::IModel:
        return appendAggregate((new Model(this))->init());
    default:
        return 0;
    }
}

} // namespace Ac
