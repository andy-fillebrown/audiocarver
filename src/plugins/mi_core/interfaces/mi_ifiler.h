/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef MI_IFILER_H
#define MI_IFILER_H

#include "mi_iunknown.h"

class IModelItem;

class IFileFiler : public IUnknown
{
public:
    enum { InterfaceType = I::IFileFiler };

    virtual QString fileName() const = 0;
    virtual void setFileName(const QString &fileName) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

class IReader : public IUnknown
{
public:
    enum { InterfaceType = I::IReader };

    virtual int nextItemType() = 0;
    virtual bool read(IModelItem *item) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

class IWriter : public IUnknown
{
public:
    enum { InterfaceType = I::IWriter };

    virtual bool write(IModelItem *item) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif
