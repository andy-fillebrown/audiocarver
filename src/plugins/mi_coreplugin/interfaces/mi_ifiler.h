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

#include "mi_iaggregate.h"

class IModelItem;

class IReader : public IAggregate
{
public:
    enum { InterfaceType = I::IReader };

    virtual int nextItemType() = 0;
    virtual bool read(IModelItem *item) = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    virtual bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IAggregate::isTypeOfInterface(interfaceType);
    }
};

class IWriter : public IAggregate
{
public:
    enum { InterfaceType = I::IWriter };

    virtual bool write(IModelItem *item) = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    virtual bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IAggregate::isTypeOfInterface(interfaceType);
    }
};

class IFileFiler : public IAggregate
{
public:
    enum { InterfaceType = I::IFileFiler };

    virtual QString fileName() const = 0;
    virtual void setFileName(const QString &fileName) = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    virtual bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IAggregate::isTypeOfInterface(interfaceType);
    }
};

#endif // MI_IFILER_H
