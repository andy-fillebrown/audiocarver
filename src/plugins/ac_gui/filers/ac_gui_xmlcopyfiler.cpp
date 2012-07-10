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

#include "ac_gui_xmlcopyfiler.h"

#include <QApplication>
#include <QClipboard>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Ac {
namespace Gui {

IAggregator *XmlCopyFiler::init()
{
    return this;
}

IAggregate *XmlCopyFiler::Reader::init()
{
    QString *data = a()->data();
    *data = QString("<clipboard>") + QApplication::clipboard()->text() + "</clipboard>";
    setStream(new QXmlStreamReader(*data));
    return XmlReader::init();
}

IAggregate *XmlCopyFiler::Writer::init()
{
    setStream(new QXmlStreamWriter(a()->data()));
    return XmlWriter::init();
}

} // namespace Gui
} // namespace Ac
