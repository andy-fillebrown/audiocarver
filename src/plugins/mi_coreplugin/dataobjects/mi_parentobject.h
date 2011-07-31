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

#ifndef MI_PARENTOBJECT_H
#define MI_PARENTOBJECT_H

#include <mi_object.h>

class MI_CORE_EXPORT MiParentObjectPrivate : public MiObjectPrivate
{
public:
    MiObject::ChangeFlags changeFlags;

    MiParentObjectPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   changeFlags(MiObject::NoChange)
    {}

    virtual ~MiParentObjectPrivate()
    {}

    template <typename T> QList<T*> &children()
    {
        return reinterpret_cast<QList<T*>&>(const_cast<QObjectList&>(q_ptr->children()));
    }

    void addChild(MiObject *child)
    {
        Q_ASSERT(child);
        Q_ASSERT(!MiObjectPrivate::children().contains(child));
        child->setParent(q_ptr);
    }

    void removeChild(MiObject *child)
    {
        Q_ASSERT(child);
        Q_ASSERT(MiObjectPrivate::children().contains(child));
        child->setParent(0);
    }

    void parentBeginChange(int i);
    void parentEndChange(int i);
};

class MI_CORE_EXPORT MiParentObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    virtual ~MiParentObject()
    {}

    const QList<MiParentObject*> &children() const
    {
        return reinterpret_cast<const QList<MiParentObject*>&>(QObject::children());
    }

    bool isChanged() const
    {
        Q_D(const MiParentObject);
        return NoChange != d->changeFlags;
    }


    void setChangeFlag(MiObject::ChangeFlag flag)
    {
        Q_D(MiParentObject);
        d->changeFlags |= flag;
    }

    void clearChangeFlags()
    {
        Q_D(MiParentObject);
        emit updated(d->changeFlags);
        d->changeFlags = MiObject::NoChange;
    }

public slots:
    virtual void update()
    {
        if (!isChanged())
            return;
        foreach (MiParentObject *child, children())
            child->update();
        clearChangeFlags();
    }

signals:
    void updated(const MiObject::ChangeFlags &changes);

protected:
    MiParentObject(MiParentObjectPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DISABLE_COPY(MiParentObject)
    Q_DECLARE_PRIVATE(MiParentObject)
    Q_DECLARE_FRIENDS(MiParentObject)
};

#endif // MI_PARENTOBJECT_H
