/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef IDATABASE_H
#define IDATABASE_H

#include <icomponent.h>
#include <iaggregate.h>
#include <isession.h>

class IModelItem;

class IDatabase : public IComponent
{
public:
    enum { InterfaceType = I::IDatabase };

    inline static IDatabase *instance()
    {
        return query<IDatabase>(ISession::instance());
    }

    virtual IModelItem *rootItem() const = 0;
    virtual const QString &fileExtension() const = 0;
    virtual const QString &fileFilter() const = 0;
    virtual QString fileName() const = 0;
    virtual void read(const QString &fileName) = 0;
    virtual void write(const QString &fileName) = 0;
    virtual bool isReading() const = 0;
    virtual void setDirty(bool dirty) = 0;
    virtual bool isDirty() const = 0;
    virtual void reset() = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IComponent::isTypeOfInterface(interfaceType);
    }
};

#endif
