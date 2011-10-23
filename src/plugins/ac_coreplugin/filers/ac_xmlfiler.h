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

#ifndef AC_XMLFILER_H
#define AC_XMLFILER_H

#include <ac_filer.h>

class XmlFileReaderPrivate;
class XmlFileReader : public FileReader
{
public:
    XmlFileReader();

    // IFileReader
    bool read(IModelItem *item);

private:
    Q_DECLARE_PRIVATE(XmlFileReader)
};

class XmlFileWriterPrivate;
class XmlFileWriter : public FileWriter
{
public:
    XmlFileWriter();

    // IFileWriter
    bool write(IModelItem *item);

private:
    Q_DECLARE_PRIVATE(XmlFileWriter)
};

#endif // AC_XMLFILER_H