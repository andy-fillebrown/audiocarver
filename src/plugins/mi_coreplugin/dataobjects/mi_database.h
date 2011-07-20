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

#ifndef MI_DATABASE_H
#define MI_DATABASE_H

#include <mi_object.h>
#include <mi_dataobjectfactory.h>
#include <mi_filerfactory.h>

namespace Private {

class MiDatabaseData
{
public:
    MiDataObjectFactory *dataObjectFactory;
    MiFilerFactory *filerFactory;

    MiDatabaseData()
        :   dataObjectFactory(0)
        ,   filerFactory(0)
    {}

    virtual ~MiDatabaseData()
    {}
};

} // namespace Private

class MI_CORE_EXPORT MiDatabase : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiDatabase)

public:
    typedef MiObject::Properties Properties;

    explicit MiDatabase(QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::MiDatabaseData)
    {
        setDataObjectFactory(new MiDataObjectFactory(this));
        setFilerFactory(new MiFilerFactory(this));
    }

    MiDatabase(MiDataObjectFactory *dataObjectFactory, QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::MiDatabaseData)
    {
        dataObjectFactory->setParent(this);
        setDataObjectFactory(dataObjectFactory);
        setFilerFactory(new MiFilerFactory(this));
    }

    MiDatabase(MiFilerFactory *filerFactory, QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::MiDatabaseData)
    {
        setDataObjectFactory(new MiDataObjectFactory(this));
        filerFactory->setParent(this);
        setFilerFactory(filerFactory);
    }

    MiDatabase(MiDataObjectFactory *dataObjectFactory, MiFilerFactory *filerFactory, QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::MiDatabaseData)
    {
        dataObjectFactory->setParent(this);
        setDataObjectFactory(dataObjectFactory);
        filerFactory->setParent(this);
        setFilerFactory(filerFactory);
    }

    virtual ~MiDatabase()
    {
        delete d;
    }

    virtual void clear()
    {}

    MiDataObjectFactory *dataObjectFactory() const
    {
        return d->dataObjectFactory;
    }

    MiFilerFactory *filerFactory() const
    {
        return d->filerFactory;
    }

protected:
    void setDataObjectFactory(MiDataObjectFactory *factory)
    {
        if (d->dataObjectFactory == factory)
            return;
        delete d->dataObjectFactory;
        d->dataObjectFactory = factory;
    }

    void setFilerFactory(MiFilerFactory *factory)
    {
        if (d->filerFactory == factory)
            return;
        delete d->filerFactory;
        d->filerFactory = factory;
    }

private:
    bool isDatabase() const
    {
        return true;
    }

    Private::MiDatabaseData *d;
};

#endif // MI_DATABASE_H
