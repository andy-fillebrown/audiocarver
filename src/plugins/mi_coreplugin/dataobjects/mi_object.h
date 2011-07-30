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

    void setChangedFlag()
    {
        if (!changed)
            changed = true;
    }

    void clearChangedFlag()
    {
        if (changed)
            changed = false;
    }

    void beginChange(int i);
    void endChange(int i);
};

class MI_CORE_EXPORT MiObject : protected QObject
{
    Q_OBJECT

public:
    enum PropertyIndex {
        IdIndex = 0,
        PropertyCount
    };

    MiObject()
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

public slots:
    virtual void update()
    {
        foreach (MiObject *child, d_ptr->children<MiObject>())
            if (child->isChanged())
                child->update();
        d_ptr->clearChangedFlag();
    }

signals:
    void aboutToChange(int i, const QVariant &value);
    void changed(int i, const QVariant &value);

protected:
    MiObject(MiObjectPrivate &dd)
        :   d_ptr(&dd)
    {}

    MiObjectPrivate *d_ptr;

private:
    Q_DISABLE_COPY(MiObject)
    Q_DECLARE_PRIVATE(MiObject)
};

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
    return const_cast<QList<T*>&>(children<T>());
}

inline
void MiObjectPrivate::addChild(MiObject *child)
{
    if (!child || children<MiObject>().contains(child))
        return;
    child->setParent(q_ptr);
    setChangedFlag();
}

inline
void MiObjectPrivate::removeChild(MiObject *child)
{
    if (!child || !children<MiObject>().contains(child))
        return;
    child->setParent(0);
    setChangedFlag();
}

class ScopedChange
{
public:
    ScopedChange(MiObjectPrivate *d, int i)
        :   d(d)
        ,   i(i)
    {
        d->beginChange(i);
    }

    ~ScopedChange()
    {
        d->endChange(i);
    }

private:
    MiObjectPrivate *d;
    int i;
};

#define changing(i) ScopedChange sc(d, i)

#endif // MI_OBJECT_H
