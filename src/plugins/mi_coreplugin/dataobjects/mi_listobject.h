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

#include <mi_parentobject.h>
#include <QMetaType>

class MiListObjectPrivate : public MiParentObjectPrivate
{
    Q_DECLARE_PUBLIC(MiParentObject)

public:
    const int propertyIndex;

    MiListObjectPrivate(MiObject *q, int propertyIndex)
        :   MiParentObjectPrivate(q)
        ,   propertyIndex(propertyIndex)
    {}

    virtual ~MiListObjectPrivate()
    {}

    template <typename T>
    QList<T*> &children() const
    {
        return reinterpret_cast<QList<T*>&>(const_cast<QObjectList&>(q_ptr->children()));
    }

    void parentBeginChange(int i)
    {
        Q_Q(MiParentObject);
        MiParentObject *parent = q->parent();
        if (parent)
            parent->d_ptr->beginChange(i);
    }

    void parentEndChange(int i)
    {
        Q_Q(MiParentObject);
        MiParentObject *parent = q->parent();
        if (parent) {
            parent->d_ptr->endChange(i);
            parent->setChangeFlag(MiObject::ChildListChanged);
        }
    }
};

class MI_CORE_EXPORT MiListObject : public MiParentObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject(int propertyIndex = 0)
        :   MiParentObject(*(new MiListObjectPrivate(this, propertyIndex)))
    {}

    virtual ~MiListObject()
    {}

    const QList<MiObject*> &children() const
    {
        return reinterpret_cast<const QList<MiObject*>&>(QObject::children());
    }

    virtual void addChild(MiObject *child)
    {
        if (!child || children().contains(child))
            return;
        Q_D(MiListObject);
        d->parentBeginChange(d->propertyIndex);
        d->addChild(child);
        d->parentEndChange(d->propertyIndex);
    }

    virtual void removeChild(MiObject *child)
    {
        if (!child || !children().contains(child))
            return;
        Q_D(MiListObject);
        d->parentBeginChange(d->propertyIndex);
        d->removeChild(child);
        d->parentEndChange(d->propertyIndex);
    }

protected:
    MiListObject(MiListObjectPrivate &dd)
        :   MiParentObject(dd)
    {}

private:
    Q_DECLARE_PRIVATE(MiListObject)
    Q_DISABLE_COPY(MiListObject)
};

Q_DECLARE_METATYPE(MiListObject*)

#endif // MI_LISTOBJECT_H
