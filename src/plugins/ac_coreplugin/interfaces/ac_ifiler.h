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

#ifndef AC_IFILER_H
#define AC_IFILER_H

#include <ac_namespace.h>

#include <mi_iunknown.h>

class IModelItem;

class IReader : public IUnknown
{
public:
    enum { Type = Ac::ReaderInterface };

    virtual bool read(IModelItem *item) = 0;
};

class IWriter : public IUnknown
{
public:
    enum { Type = Ac::WriterInterface };

    virtual bool write(IModelItem *item) = 0;
};

class IFileFiler : public IUnknown
{
public:
    enum { Type = Ac::FileFilerInterface };

    virtual QString fileName() const = 0;
    virtual void setFileName(const QString &fileName) = 0;
    virtual void close() = 0;
};

class ICopyFiler : public IUnknown
{
public:
    enum { Type = Ac::CopyFilerInterface };

    virtual const QString &data() const = 0;
};

#endif // AC_IFILER_H
