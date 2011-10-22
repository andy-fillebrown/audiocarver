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

#ifndef AC_UNDOFILER_H
#define AC_UNDOFILER_H

#include <ac_filer.h>

class UndoReaderPrivate;
class UndoReader : public FileReader
{
public:
    UndoReader();

    // IFileReader
    bool read(IModelItem *item);

private:
    Q_DECLARE_PRIVATE(UndoReader)
};

class UndoWriterPrivate;
class UndoWriter : public FileWriter
{
public:
    UndoWriter();

    // IFileWriter
    bool write(IModelItem *item);

private:
    Q_DECLARE_PRIVATE(UndoWriter)
};

#endif // AC_UNDOFILER_H
