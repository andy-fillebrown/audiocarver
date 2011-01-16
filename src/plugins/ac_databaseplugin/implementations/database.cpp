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

DatabaseImpl::DatabaseImpl()
{
}

DatabaseImpl::~DatabaseImpl()
{
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
    static QString dummy;
    return dummy;
}

void DatabaseImpl::clear()
{
}

void DatabaseImpl::read(const QString &fileName)
{
    Q_UNUSED(fileName);
}

void DatabaseImpl::write(const QString &fileName)
{
    Q_UNUSED(fileName);
}
