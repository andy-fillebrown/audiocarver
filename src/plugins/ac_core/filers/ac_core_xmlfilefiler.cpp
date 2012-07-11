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

#include "ac_core_xmlfilefiler.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Ac {
namespace Core {

IAggregator *XmlFileFiler::init()
{
    return this;
}

XmlFileFiler::~XmlFileFiler()
{
    delete _file;
}

QString XmlFileFiler::fileName() const
{
    if (!_file)
        return QString();
    return _file->fileName();
}

void XmlFileFiler::setFileName(const QString &fileName)
{
    if (this->fileName() == fileName)
        return;
    delete _file;
    _file = new QFile(fileName);
}

IAggregate *XmlFileFiler::FileFiler::init()
{
    return this;
}

IAggregate *XmlFileFiler::Reader::init()
{
    QFile *file = a()->file();
    if (file && file->open(QIODevice::ReadOnly))
        setStream(new QXmlStreamReader(file));
    return XmlReader::init();
}

IAggregate *XmlFileFiler::Writer::init()
{
    QFile *file = a()->file();
    if (file && file->open(QIODevice::WriteOnly))
        setStream(new QXmlStreamWriter(file));
    return XmlWriter::init();
}

} // namespace Core
} // namespace Ac
