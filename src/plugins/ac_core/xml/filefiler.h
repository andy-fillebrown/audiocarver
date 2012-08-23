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

#ifndef XML_FILEFILER_H
#define XML_FILEFILER_H

#include <interfaces/ifilefiler.h>

class IAggregate;
class QFile;

namespace Xml {

class FileFiler : public IFileFiler
{
    IAggregate *_aggregate;
    QFile *_file;

public:
    FileFiler(IAggregate *aggregate)
        :   _aggregate(aggregate)
        ,   _file(0)
    {}

    virtual IUnknown *initialize();
    ~FileFiler();
    void *queryInterface(int interfaceType) const;

protected:
    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    QFile *file() const
    {
        return _file;
    }

    QString fileName() const;
    void setFileName(const QString &fileName);
};

}

#endif
