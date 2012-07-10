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

#ifndef AC_XMLREADER_H
#define AC_XMLREADER_H

#include "mi_ifiler.h"

#include <ac_coreglobal.h>

class QXmlStreamReader;

class AC_CORE_EXPORT XmlReader : public IReader
{
    IAggregator *_aggregator;
    QXmlStreamReader *_stream;

protected:
    XmlReader(IAggregator *aggregator)
        :   _aggregator(aggregator)
        ,   _stream(0)
    {}

    virtual IAggregate *init();
    ~XmlReader();

    IAggregator *a() const
    {
        return _aggregator;
    }

    QXmlStreamReader *stream()
    {
        return _stream;
    }

    void setStream(QXmlStreamReader *stream);

    // IReader
    int nextItemType();
    bool read(IModelItem *item);

    // IAggregate
    IAggregator *aggregator() const
    {
        return _aggregator;
    }
};

#endif // AC_XMLREADER_H
