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

#include "ac_core_filefiler.h"
#include <iaggregate.h>
#include <QFile>

namespace Xml {

FileFiler::FileFiler(IAggregate *aggregate)
    :   _aggregate(aggregate)
    ,   _file(0)
{
    _aggregate->append(this);
}

FileFiler::~FileFiler()
{
    delete _file;
}

void *FileFiler::queryInterface(int interfaceType) const
{
    void *i = IFileFiler::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

QString FileFiler::fileName() const
{
    if (!_file)
        return QString();
    return _file->fileName();
}

void FileFiler::setFileName(const QString &fileName)
{
    if (this->fileName() == fileName)
        return;
    delete _file;
    _file = new QFile(fileName);
}

}
