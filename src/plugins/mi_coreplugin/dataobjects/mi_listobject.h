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
#include <QMetaType>

class MiListObjectPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiObject)

public:
    const int propertyIndex;
    MiObject::ChangeFlags changeFlags;

    MiListObjectPrivate(MiObject *q, int propertyIndex)
        :   MiObjectPrivate(q)
        ,   propertyIndex(propertyIndex)
        ,   changeFlags(MiObject::NoChange)
    {}

    virtual ~MiListObjectPrivate()
    {}

    template <typename T>
    QList<T*> &children() const
    {
        return reinterpret_cast<QList<T*>&>(const_cast<QObjectList&>(q_ptr->children()));
    }

    void parentBeginChange(int i);
    void parentEndChange(int i);
};

class MI_CORE_EXPORT MiListObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject(int propertyIndex = 0)
        :   MiObject(*(new MiListObjectPrivate(this, propertyIndex)))
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
        setChangeFlag(MiObject::ChildListChanged);
    }

    virtual void removeChild(MiObject *child)
    {
        if (!child || !children().contains(child))
            return;
        Q_D(MiListObject);
        d->parentBeginChange(d->propertyIndex);
        d->removeChild(child);
        d->parentEndChange(d->propertyIndex);
        setChangeFlag(MiObject::ChildListChanged);
    }

    bool isChanged() const
    {
        Q_D(const MiListObject);
        return MiObject::NoChange != d->changeFlags;
    }

    void setChangeFlag(MiObject::ChangeFlag flag)
    {
        Q_D(MiListObject);
        d->changeFlags |= flag;
    }

public slots:
    virtual void update()
    {
        if (isChanged()) {
            Q_D(MiListObject);
            emit updated(d->changeFlags);
            d->changeFlags = MiObject::NoChange;
        }
    }

signals:
    void updated(const MiObject::ChangeFlags &changes);

protected:
    MiListObject(MiListObjectPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DISABLE_COPY(MiListObject)
    Q_DECLARE_PRIVATE(MiListObject)

    friend MiListObject *qobject_cast<MiListObject*>(QObject*);
};

inline
void MiListObjectPrivate::parentBeginChange(int i)
{
    Q_Q(MiObject);
    MiListObject *parent = q->parent();
    if (parent)
        parent->d_ptr->beginChange(i);
}

inline
void MiListObjectPrivate::parentEndChange(int i)
{
    Q_Q(MiObject);
    MiListObject *parent = q->parent();
    if (parent) {
        parent->d_ptr->endChange(i);
    }
}

Q_DECLARE_METATYPE(MiListObject*)

#endif // MI_LISTOBJECT_H
