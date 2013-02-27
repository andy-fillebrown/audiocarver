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
#include "ac_core_namespace.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>
#include <ifilefiler.h>
#include <ifilerfactory.h>
#include <imodel.h>
#include <imodelitem.h>
#include <ireader.h>
#include <iwriter.h>

using namespace Ac;

namespace Core {

Database::Database()
    :   _score(0)
{
    _score = IDatabaseObjectFactory::instance()->create(ScoreItem);
}

Database::~Database()
{
    delete _score;
}

IModelItem *Database::rootItem() const
{
    return QUERY(IModelItem, _score);
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
    IModel::instance()->reset();
    rootItem()->reset();
    _fileName.clear();
}

void Database::read(const QString &fileName)
{
    reset();
    IAggregate *filer = IFilerFactory::instance()->create(FileFiler);
    QUERY(IFileFiler, filer)->setFileName(fileName);
    if (QUERY(IReader, filer)->read(rootItem()))
        _fileName = fileName;
    delete filer;
}

void Database::write(const QString &fileName)
{
    IAggregate *filer = IFilerFactory::instance()->create(FileFiler);
    QUERY(IFileFiler, filer)->setFileName(fileName);
    QUERY(IWriter, filer)->write(rootItem());
    delete filer;
}

bool Database::isReading() const
{
//    return d->reading;
    return false;
}

}
