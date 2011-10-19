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

class IFiler : public IUnknown
{
public:
    virtual bool setFileName(const QString &fileName) = 0;
};

class IFileReader : public IFiler
{
public:
    virtual bool read(IModelItem *item) = 0;
};

class IFileWriter : public IFiler
{
public:
    virtual bool write(IModelItem *item) = 0;
};

#endif // AC_IFILER_H
