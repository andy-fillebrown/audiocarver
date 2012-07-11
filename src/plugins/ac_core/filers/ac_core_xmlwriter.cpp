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

#include "ac_core_xmlwriter.h"

#include <QXmlStreamWriter>

namespace Ac {
namespace Core {

IAggregate *XmlWriter::init()
{
    return this;
}

XmlWriter::~XmlWriter()
{
    delete _stream;
}

void XmlWriter::setStream(QXmlStreamWriter *stream)
{
    if (_stream == stream)
        return;
    delete _stream;
    _stream = stream;
}

bool XmlWriter::write(IModelItem *item)
{
    return false;
}

} // namespace Core
} // namespace Ac
