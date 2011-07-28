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

#ifndef MI_LISTOBJECT_H
#define MI_LISTOBJECT_H

#include <mi_object.h>

class MiListObject;

class MI_CORE_EXPORT MiListObjectPrivate : public MiObjectPrivate
{
public:
    MiListObjectPrivate(MiObject *q)
        :   MiObjectPrivate(q)
    {}

    virtual ~MiListObjectPrivate()
    {}

    template <typename T>
    QList<T*> &items()
    {
        return reinterpret_cast<QList<T*>&>(children());
    }
};

class MI_CORE_EXPORT MiListObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject()
        :   MiObject(*(new MiObjectPrivate(this)))
    {}

    virtual ~MiListObject()
    {}

    const QList<MiObject*> &items() const
    {
        Q_D(const MiListObject);
        return d->children();
    }

    virtual void addItem(MiObject *item)
    {
        if (children().contains(item))
            return;
        Q_D(MiListObject);
        emit aboutToChange();
        d->addChild(item);
        emit changed();
        setChangedFlags(MiObject::ListChanged);
    }

    virtual void removeItem(MiObject *item)
    {
        if (!children().contains(item))
            return;
        Q_D(MiListObject);
        emit aboutToChange();
        d->removeChild(item);
        emit changed();
        setChangedFlags(MiObject::ListChanged);
    }

protected:
    MiListObject(MiListObjectPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DECLARE_PRIVATE(MiListObject)
    Q_DISABLE_COPY(MiListObject)
};

#endif // MI_LISTOBJECT_H
