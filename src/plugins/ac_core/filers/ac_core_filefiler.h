/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_CORE_FILEFILER_H
#define AC_CORE_FILEFILER_H

#include <ifiler.h>

class IAggregate;
class QFile;

namespace Xml {

class FileFiler : public IFiler
{
    IAggregate *_aggregate;
    QFile *_file;
    QXmlStreamReader *_reader;
    QXmlStreamWriter *_writer;

public:
    FileFiler(IAggregate *aggregate);
    ~FileFiler();

    void *queryInterface(int interfaceType) const;

protected:
    void initialize()
    {}

    void reset()
    {}

    QString fileName() const;
    void setFileName(const QString &fileName);
    QXmlStreamReader *reader();
    QXmlStreamWriter *writer();
};

}

#endif
