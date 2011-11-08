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
class XmlFileReader : public FileFiler
        ,   public IReader
{
public:
    XmlFileReader(QObject *parent = 0);

    // IReader
    bool read(IModelItem *item);

    // IUnknown
    void *query(int type) const
    {
        if (IReader::Type == type)
            return objectToInterface_cast<IReader>(this);
        return FileFiler::query(type);
    }

private:
    Q_DECLARE_PRIVATE(XmlFileReader)
};

class XmlFileWriterPrivate;
class XmlFileWriter : public FileFiler
        ,   public IWriter
{
public:
    XmlFileWriter(QObject *parent = 0);
    ~XmlFileWriter();

    // IWriter
    bool write(IModelItem *item);

    // IUnknown
    void *query(int type) const
    {
        if (IWriter::Type == type)
            return objectToInterface_cast<IWriter>(this);
        return FileFiler::query(type);
    }

private:
    Q_DECLARE_PRIVATE(XmlFileWriter)
};

class XmlCopyReaderPrivate;
class XmlCopyReader : public CopyFiler
        ,   public IReader
{
public:
    XmlCopyReader(QObject *parent = 0);

    // ICopyFiler
    int nextItemType() const;

    // IReader
    bool read(IModelItem *item);

    // IUnknown
    void *query(int type) const
    {
        if (IReader::Type == type)
            return objectToInterface_cast<IReader>(this);
        return CopyFiler::query(type);
    }

private:
    Q_DECLARE_PRIVATE(XmlCopyReader)
};

class XmlCopyWriterPrivate;
class XmlCopyWriter : public CopyFiler
        ,   public IWriter
{
public:
    XmlCopyWriter(QObject *parent = 0);
    ~XmlCopyWriter();

    // ICopyFiler
    int nextItemType() const
    {
        return Mi::UnknownItem;
    }

    // IWriter
    bool write(IModelItem *item);

    // IUnknown
    void *query(int type) const
    {
        if (IWriter::Type == type)
            return objectToInterface_cast<IWriter>(this);
        return CopyFiler::query(type);
    }

private:
    Q_DECLARE_PRIVATE(XmlCopyWriter)
};

#endif // AC_XMLFILER_H
