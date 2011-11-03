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

#ifndef AC_FILER_H
#define AC_FILER_H

#include <ac_ifiler.h>
#include <ac_global.h>

#include <QFile>

class FilerPrivate;
class Filer
{
protected:
    Filer(FilerPrivate &dd)
        :   d_ptr(&dd)
    {}

    QScopedPointer<FilerPrivate> d_ptr;
};

class FilerPrivate
{
public:
    Filer *q_ptr;
    QFile file;

    FilerPrivate(Filer *q)
        :   q_ptr(q)
    {}

    virtual ~FilerPrivate() {}

    virtual void setFileName(const QString &fileName)
    {
        if (file.fileName() == fileName)
            return;
        file.setFileName(fileName);
    }

    virtual QIODevice::OpenMode openMode() const = 0;

    virtual bool openFile()
    {
        if (file.isOpen())
            return true;
        return file.open(openMode());
    }

    void closeFile()
    {
        if (file.isOpen())
            file.close();
    }
};

class FileReaderPrivate;
class FileReader : public Filer
        ,   public IFileReader
{
public:
    // IFiler
    inline QString fileName() const;
    inline void setFileName(const QString &fileName);
    inline void close();

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::FileReaderInterface:
            return objectToInterface_cast<IFileReader>(this);
        default:
            return 0;
        }
    }

protected:
    inline FileReader(FileReaderPrivate &dd);

private:
    Q_DECLARE_PRIVATE(FileReader)
};

class FileReaderPrivate : public FilerPrivate
{
public:
    FileReaderPrivate(FileReader *q)
        :   FilerPrivate(q)
    {}
};

inline FileReader::FileReader(FileReaderPrivate &dd)
    :   Filer(dd)
{}

inline QString FileReader::fileName() const
{
    Q_D(const FileReader);
    return d->file.fileName();
}

inline void FileReader::setFileName(const QString &fileName)
{
    Q_D(FileReader);
    d->setFileName(fileName);
}

inline void FileReader::close()
{
    Q_D(FileReader);
    d->closeFile();
}

class FileWriterPrivate;
class FileWriter : public Filer
        ,   public IFileWriter
{
public:
    // IFiler
    inline QString fileName() const;
    inline void setFileName(const QString &fileName);
    inline void close();

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::FileWriterInterface:
            return objectToInterface_cast<IFileWriter>(this);
        default:
            return 0;
        }
    }

protected:
    inline FileWriter(FileWriterPrivate &dd);

private:
    Q_DECLARE_PRIVATE(FileWriter)
};

class FileWriterPrivate : public FilerPrivate
{
public:
    FileWriterPrivate(FileWriter *q)
        :   FilerPrivate(q)
    {}
};

inline FileWriter::FileWriter(FileWriterPrivate &dd)
    :   Filer(dd)
{}

inline QString FileWriter::fileName() const
{
    Q_D(const FileWriter);
    return d->file.fileName();
}

inline void FileWriter::setFileName(const QString &fileName)
{
    Q_D(FileWriter);
    d->setFileName(fileName);
}

inline void FileWriter::close()
{
    Q_D(FileWriter);
    d->closeFile();
}

#endif // AC_FILER_H
