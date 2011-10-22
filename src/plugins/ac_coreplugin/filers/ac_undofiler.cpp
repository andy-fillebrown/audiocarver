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

#include "ac_undofiler.h"

class UndoReaderPrivate : public FileReaderPrivate
{
public:
    UndoReaderPrivate(UndoReader *q)
        :   FileReaderPrivate(q)
    {}
};

UndoReader::UndoReader()
    :   FileReader(*(new UndoReaderPrivate(this)))
{}

bool UndoReader::read(IModelItem *item)
{
    Q_UNUSED(item);
    return false;
}

class UndoWriterPrivate : public FileWriterPrivate
{
public:
    UndoWriterPrivate(UndoWriter *q)
        :   FileWriterPrivate(q)
    {}
};

UndoWriter::UndoWriter()
    :   FileWriter(*(new UndoWriterPrivate(this)))
{}

bool UndoWriter::write(IModelItem *item)
{
    Q_UNUSED(item);
    return false;
}
