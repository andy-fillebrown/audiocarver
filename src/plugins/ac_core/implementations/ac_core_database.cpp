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

#include "ac_core_database.h"

#include "ac_core_dataobjectfactory.h"
#include "ac_core_filerfactory.h"
#include "ac_core_model.h"

#include <mi_ifiler.h>
#include <mi_imodelitem.h>

#include <ac_core_namespace.h>

namespace Ac {
namespace Core {

IAggregator *Database::init()
{
    _score = query<IDataObjectFactory>(this)->create(ScoreItem);
    return Mi::Core::Database::init();
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
    return _fileName;
}

void Database::reset()
{
    score()->clear();
    _fileName.clear();
}

void Database::read(const QString &fileName)
{
    reset();
    IAggregator *filer = query<IFilerFactory>(this)->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    if (query<IReader>(filer)->read(query<IModelItem>(_score)))
        _fileName = fileName;
    delete filer;
}

void Database::write(const QString &fileName)
{
//    emit databaseAboutToBeWritten();
//    IWriter *writer = IFilerFactory::instance()->createWriter(FileFiler);
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
    case I::IDataObjectFactory:
        return appendAggregate((new DataObjectFactory(this))->init());
    case I::IFilerFactory:
        return appendAggregate((new FilerFactory(this))->init());
    case I::IModel:
        return appendAggregate((new Model(this))->init());
    default:
        return 0;
    }
}

} // namespace Core
} // namespace Ac
