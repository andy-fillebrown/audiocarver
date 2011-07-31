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
#include <QMetaType>
#include <QObject>

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

class MI_CORE_EXPORT MiObjectPrivate
{
public:
    MiObject *q_ptr;
    bool changed;

    MiObjectPrivate(MiObject *q)
        :   q_ptr(q)
        ,   changed(true)
    {}

    virtual ~MiObjectPrivate()
    {}

    template <typename T>
    T* parent() const;

    template <typename T>
    const QList<T*> &children() const;

    template <typename T>
    QList<T*> &children();

    void addChild(MiObject *child);
    void removeChild(MiObject *child);

    void setChangedFlag();

    void clearChangedFlag()
    {
        if (changed)
            changed = false;
    }

    void beginChange(int i);
    void endChange(int i);
    void parentBeginChange(int i);
    void parentEndChange(int i);
};

class MI_CORE_EXPORT MiObject : protected QObject
{
    Q_OBJECT

public:
    enum PropertyIndex {
        IdIndex = 0,
        PropertyCount
    };

    explicit MiObject(int i = 0)
        :   d_ptr(new MiObjectPrivate(this))
    {}

    virtual ~MiObject()
    {
        delete d_ptr;
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

    bool isChanged() const
    {
        return d_ptr->changed;
    }

    template <typename T>
    T *cast()
    {
        return qobject_cast<T*>(this);
    }

    static bool connect(const MiObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType type = Qt::UniqueConnection)
    {
        return QObject::connect(sender, signal, receiver, member, type);
    }

    bool disconnect(const QObject *receiver, const char *member = 0)
    {
        return QObject::disconnect(receiver, member);
    }

public slots:
    virtual void update()
    {
        foreach (MiObject *child, d_ptr->children<MiObject>())
            child->update();
        d_ptr->clearChangedFlag();
    }

signals:
    void aboutToChange(int i);
    void changed(int i = -1);

protected:
    MiObject(MiObjectPrivate &dd)
        :   d_ptr(&dd)
    {}

    MiObjectPrivate *d_ptr;

private:
    Q_DISABLE_COPY(MiObject)
    Q_DECLARE_PRIVATE(MiObject)
    Q_DECLARE_FRIENDS(MiObject)
};

Q_DECLARE_METATYPE(MiObject*)

template <typename T> inline
T* MiObjectPrivate::parent() const
{
    return qobject_cast<T*>(q_ptr->parent());
}

template <typename T> inline
const QList<T*> &MiObjectPrivate::children() const
{
    return reinterpret_cast<const QList<T*>&>(q_ptr->children());
}

template <typename T> inline
QList<T*> &MiObjectPrivate::children()
{
    return reinterpret_cast<QList<T*>&>(const_cast<QObjectList&>(q_ptr->children()));
}

inline
void MiObjectPrivate::addChild(MiObject *child)
{
    Q_ASSERT(child);
    Q_ASSERT(!children<MiObject>().contains(child));
    child->setParent(q_ptr);
}

inline
void MiObjectPrivate::removeChild(MiObject *child)
{
    Q_ASSERT(child);
    Q_ASSERT(children<MiObject>().contains(child));
    child->setParent(0);
}

inline
void MiObjectPrivate::setChangedFlag()
{
    if (changed)
        return;
    changed = true;
    MiObject *parent = this->parent<MiObject>();
    if (parent)
        parent->d_ptr->setChangedFlag();
}

inline
void MiObjectPrivate::beginChange(int i)
{
    q_ptr->emit aboutToChange(i);
}

inline
void MiObjectPrivate::endChange(int i)
{
    q_ptr->emit changed(i);
    setChangedFlag();
}

inline
void MiObjectPrivate::parentBeginChange(int i)
{
    if (i < 1)
        return;
    MiObject *parent = this->parent<MiObject>();
    if (parent)
        parent->d_ptr->beginChange(i);
}

inline
void MiObjectPrivate::parentEndChange(int i)
{
    if (i < 1)
        return;
    MiObject *parent = this->parent<MiObject>();
    if (parent)
        parent->d_ptr->endChange(i);
}

#endif // MI_OBJECT_H
