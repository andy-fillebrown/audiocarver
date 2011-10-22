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

#include <QString>

class FilerPrivate;
class Filer
{
public:
    ~Filer();

protected:
    Filer(FilerPrivate &dd)
        :   d_ptr(&dd)
    {}

    FilerPrivate *d_ptr;
};

class FilerPrivate
{
public:
    Filer *q_ptr;
    QString fileName;

    FilerPrivate(Filer *q)
        :   q_ptr(q)
    {}

    virtual ~FilerPrivate() {}

    virtual void setFileName(const QString &fileName)
    {
        if (this->fileName == fileName)
            return;
        this->fileName = fileName;
    }
};

class FileReaderPrivate;
class FileReader : public Filer
        ,   public IFileReader
{
public:
    // IFiler
    inline void setFileName(const QString &fileName);

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::FileReaderInterface:
            return Q_I(IFileReader);
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

inline void FileReader::setFileName(const QString &fileName)
{
    Q_D(FileReader);
    d->setFileName(fileName);
}

class FileWriterPrivate;
class FileWriter : public Filer
        ,   public IFileWriter
{
public:
    // IFiler
    inline void setFileName(const QString &fileName);

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::FileWriterInterface:
            return Q_I(IFileWriter);
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

inline void FileWriter::setFileName(const QString &fileName)
{
    Q_D(FileWriter);
    d->setFileName(fileName);
}

#endif // AC_FILER_H
