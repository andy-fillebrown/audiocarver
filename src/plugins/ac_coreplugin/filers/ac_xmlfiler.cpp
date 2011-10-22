/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "ac_xmlfiler.h"

class XmlFileReaderPrivate : public FileReaderPrivate
{
public:
    XmlFileReaderPrivate(XmlFileReader *q)
        :   FileReaderPrivate(q)
    {}
};

XmlFileReader::XmlFileReader()
    :   FileReader(*(new XmlFileReaderPrivate(this)))
{}

bool XmlFileReader::read(IModelItem *item)
{
    Q_UNUSED(item);
    return false;
}

class XmlFileWriterPrivate : public FileWriterPrivate
{
public:
    XmlFileWriterPrivate(XmlFileWriter *q)
        :   FileWriterPrivate(q)
    {}
};

XmlFileWriter::XmlFileWriter()
    :   FileWriter(*(new XmlFileWriterPrivate(this)))
{}

bool XmlFileWriter::write(IModelItem *item)
{
    Q_UNUSED(item);
    return false;
}
