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

#ifndef AC_XML_WRITER_H
#define AC_XML_WRITER_H

#include <mi_iwriter.h>
#include "ac_core_global.h"

class IAggregate;
class QXmlStreamWriter;

namespace Xml {

class AC_CORE_EXPORT Writer : public IWriter
{
    IAggregate *_aggregate;
    QXmlStreamWriter *_stream;

public:
    Writer(IAggregate *aggregate)
        :   _aggregate(aggregate)
        ,   _stream(0)
    {}

    virtual IUnknown *initialize();
    ~Writer();
    void *queryInterface(int interfaceType) const;

protected:
    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    QXmlStreamWriter *stream()
    {
        return _stream;
    }

    void setStream(QXmlStreamWriter *stream);
    bool write(IModelItem *item);
};

}

#endif
