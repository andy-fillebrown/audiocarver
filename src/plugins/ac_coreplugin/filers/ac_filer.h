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

class Filer;
class FilerPrivate
{
public:
    Filer *q_ptr;
    QFile file;

    FilerPrivate(Filer *q)
        :   q_ptr(q)
    {}

    virtual ~FilerPrivate() {}

    virtual QIODevice::OpenMode openMode() const = 0;

    virtual bool openFile()
    {
        if (file.isOpen())
            return true;
        return file.open(openMode());
    }
};

class Filer : public QObject
        ,   public IFileFiler
{
public:
    // IFileFiler
    QString fileName() const
    {
        return d_ptr->file.fileName();
    }

    void setFileName(const QString &fileName)
    {
        if (d_ptr->file.fileName() == fileName)
            return;
        d_ptr->file.setFileName(fileName);
    }

    void close()
    {
        if (d_ptr->file.isOpen())
            d_ptr->file.close();
    }

    // IUnknown
    void *query(int type) const
    {
        if (IFileFiler::Type == type)
            return objectToInterface_cast<IFileFiler>(this);
        return 0;
    }

protected:
    Filer(FilerPrivate &dd, QObject *parent)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    QScopedPointer<FilerPrivate> d_ptr;
};

#endif // AC_FILER_H
