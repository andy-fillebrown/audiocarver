/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "database.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

DatabaseImpl *s_instance = 0;

Database::IDatabase *DatabaseImpl::instance()
{
    return s_instance;
}

DatabaseImpl::DatabaseImpl()
{
    s_instance = this;
}

DatabaseImpl::~DatabaseImpl()
{
    s_instance = 0;
}

const QString &DatabaseImpl::fileExtension() const
{
    static QString ext = QString::fromLatin1(".ac");
    return ext;
}

const QString &DatabaseImpl::fileFilter() const
{
    static QString filter = QString::fromLatin1("AudioCarver (*%1)").arg(fileExtension());
    return filter;
}

const QString &DatabaseImpl::fileName() const
{
    return _fileName;
}

void DatabaseImpl::clear()
{
    _fileName = QString::fromLatin1("");
}

void DatabaseImpl::read(const QString &fileName)
{
    _fileName = fileName;
}

void DatabaseImpl::write(const QString &fileName)
{
    _fileName = fileName;
}

const QString &DatabaseImpl::addUniqueName(const QString &requestedName)
{
    Q_UNUSED(requestedName);
    static QString dummy;
    return dummy;
}

Database::IRootObject *DatabaseImpl::rootObject() const
{
    return 0;
}

Database::IObject *DatabaseImpl::object(const QString &name) const
{
    Q_UNUSED(name);
    return 0;
}
