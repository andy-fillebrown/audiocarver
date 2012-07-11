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

#ifndef AC_CORE_XMLWRITER_H
#define AC_CORE_XMLWRITER_H

#include "mi_ifiler.h"

#include <ac_core_global.h>

class QXmlStreamWriter;

namespace Ac {
namespace Core {

class AC_CORE_EXPORT XmlWriter : public IWriter
{
    IAggregator *_aggregator;
    QXmlStreamWriter *_stream;

protected:
    XmlWriter(IAggregator *aggregator)
        :   _aggregator(aggregator)
        ,   _stream(0)
    {}

    virtual IAggregate *init();
    ~XmlWriter();

    IAggregator *a() const
    {
        return _aggregator;
    }

    QXmlStreamWriter *stream()
    {
        return _stream;
    }

    void setStream(QXmlStreamWriter *stream);

    // IWriter
    bool write(IModelItem *item);

    // IAggregate
    IAggregator *aggregator() const
    {
        return _aggregator;
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_XMLWRITER_H
