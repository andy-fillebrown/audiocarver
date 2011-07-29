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

#ifndef MI_OBJECT_H
#define MI_OBJECT_H

#include <mi_core_global.h>
#include <QObject>
#include <QVariant>

// Redefine Q_OBJECT to declare meta-object members as protected, not public.
#undef Q_OBJECT
#define Q_OBJECT \
protected: \
    Q_OBJECT_CHECK \
    static const QMetaObject staticMetaObject; \
    Q_OBJECT_GETSTATICMETAOBJECT \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    QT_TR_FUNCTIONS \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
private:

class MiObject;
class MiObjectPrivate;

class MiObjectData
{
public:
    MiObject *q_ptr;
    quint32 changedFlags;

    MiObjectData(MiObject *q)
        :   q_ptr(q)
        ,   changedFlags(0)
    {}

    virtual ~MiObjectData()
    {}

    const QList<MiObject*> &children() const;
    QObjectList &children();

};

class MI_CORE_EXPORT MiObject : protected QObject
{
    Q_OBJECT

public:
    enum PropertyIndex {
        IdIndex = 0,
        PropertyCount
    };

    enum ChangedFlag {
        NoChange = 0x0,
        ListChanged = 0x2,
        ListItemChanged = 0x4,
        ListItemSortValueChanged = 0x8 | ListItemChanged,
        EverythingChanged = 0xf
    };
    Q_DECLARE_FLAGS(ChangedFlags, ChangedFlag)

    MiObject()
        :   d_ptr(new MiObjectData(this))
    {}

    virtual ~MiObject()
    {
        delete d_ptr;
    }

    MiObject *parent() const
    {
        return static_cast<MiObject*>(QObject::parent());
    }

    QString className() const
    {
        return metaObject()->className();
    }

    int propertyCount() const
    {
        return metaObject()->propertyCount();
    }

    int propertyIndex(const QString propertyName) const
    {
        return metaObject()->indexOfProperty(qPrintable(propertyName));
    }

    QString propertyType(int i) const;
    bool isPropertyWritable(int i) const;
    QString propertyName(int i) const;
    QVariant propertyValue(int i) const;
    void setPropertyValue(int i, const QVariant &value);

    ChangedFlags changedFlags() const
    {
        return ChangedFlags(d_ptr->changedFlags);
    }

    void setChangedFlag(ChangedFlag flag = EverythingChanged, bool enabled = true)
    {
        if (enabled)
            setChangedFlags(ChangedFlags(d_ptr->changedFlags) | flag);
        else
            setChangedFlags(ChangedFlags(d_ptr->changedFlags) & ~flag);
    }

    void setChangedFlags(const ChangedFlags &flags = EverythingChanged)
    {
        if (flags == ChangedFlags(d_ptr->changedFlags))
            return;
        d_ptr->changedFlags = flags;
        emit changedFlagsChanged(ChangedFlags(d_ptr->changedFlags));
    }

public slots:
    virtual void update()
    {
        setChangedFlags(NoChange);
    }

signals:
    void aboutToChange(int i = -1, const QVariant &value = QVariant());
    void changed(int i = -1, const QVariant &value = QVariant());
    void changedFlagsChanged(const ChangedFlags &flags = EverythingChanged);

protected:
    MiObject(MiObjectData &dd)
        :   d_ptr(&dd)
    {}

    MiObjectData *d_ptr;

private:
    Q_DISABLE_COPY(MiObject)
    friend class MiObjectData;
    friend class MiObjectPrivate;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MiObject::ChangedFlags)

inline const QList<MiObject*> &MiObjectData::children() const
{
    return reinterpret_cast<const QList<MiObject*>&>(q_ptr->children());
}

inline QObjectList &MiObjectData::children()
{
    return const_cast<QObjectList&>(q_ptr->children());
}

class MiObjectPrivate : public MiObjectData
{
    Q_DECLARE_PUBLIC(MiObject)

public:
    MiObjectPrivate(MiObject *q)
        :   MiObjectData(q)
    {}

    virtual ~MiObjectPrivate()
    {}

    QObject *parent() const
    {
        return q_ptr->parent();
    }

    void addChild(MiObject *child)
    {
        if (!child)
            return;
        child->setParent(q_ptr);
    }

    void removeChild(MiObject *child)
    {
        if (!child)
            return;
        child->setParent(0);
    }

    void addParentChangedFlags(const MiObject::ChangedFlags &flags)
    {
        Q_Q(MiObject);
        MiObject *parent = q->parent();
        if (parent)
            parent->setChangedFlags(MiObject::ChangedFlags(changedFlags) | flags);
    }
};

#endif // MI_OBJECT_H
