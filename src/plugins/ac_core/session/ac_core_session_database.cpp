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

#include "ac_core_session_database.h"
#include <mi_core_iaggregate.h>
#include <mi_core_iclassfactory.h>
#include <mi_core_ifilefiler.h>
#include <mi_core_ifilerfactory.h>
#include <mi_core_imodel.h>
#include <mi_core_imodelitem.h>
#include <mi_core_ireader.h>
#include <mi_core_iwriter.h>
#include "ac_core_namespace.h"

using namespace Ac;

namespace Session {

IUnknown *Database::initialize()
{
    _score = IClassFactory::instance()->create(ScoreItem);
    return Base::Database::initialize();
}

Database::~Database()
{
    delete _score;
}

IModelItem *Database::rootItem() const
{
    return query<IModelItem>(_score);
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
    rootItem()->reset();
    _fileName.clear();
}

void Database::read(const QString &fileName)
{
    reset();
    IAggregate *filer = IFilerFactory::instance()->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    if (query<IReader>(filer)->read(rootItem()))
        _fileName = fileName;
    delete filer;
}

void Database::write(const QString &fileName)
{
    IAggregate *filer = IFilerFactory::instance()->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    query<IWriter>(filer)->write(rootItem());
    delete filer;
}

bool Database::isReading() const
{
//    return d->reading;
    return false;
}

}
