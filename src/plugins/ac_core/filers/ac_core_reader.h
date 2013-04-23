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

#ifndef AC_CORE_READER_H
#define AC_CORE_READER_H

#include <ireader.h>
#include "ac_core_global.h"

class IAggregate;
class QXmlStreamReader;

namespace Xml {

class AC_CORE_EXPORT Reader : public IReader
{
    IAggregate *_aggregate;
    QXmlStreamReader *_stream;

public:
    Reader(IAggregate *aggregate);
    ~Reader();

    void *queryInterface(int interfaceType) const;

protected:
    void initialize()
    {}

    void reset()
    {}

    void setStream(QXmlStreamReader *stream);
    int nextItemType();
    bool read(IModelItem *item);
};

}

#endif
