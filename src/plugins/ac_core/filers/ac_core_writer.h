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

#ifndef AC_CORE_WRITER_H
#define AC_CORE_WRITER_H

#include <iwriter.h>
#include "ac_core_global.h"

class IAggregate;
class QXmlStreamWriter;

namespace Xml {

class AC_CORE_EXPORT Writer : public IWriter
{
    IAggregate *_aggregate;
    QXmlStreamWriter *_writer;

public:
    Writer(IAggregate *aggregate);

    void *queryInterface(int interfaceType) const;

protected:
    void initialize()
    {}

    void reset()
    {}

    bool writeStartElement(const QString &elementName);
    bool writeEndElement();
    bool write(IModelItem *item);
};

}

#endif
