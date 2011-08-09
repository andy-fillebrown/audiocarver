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
#include <aggregate.h>
#include <QMetaType>

// Redefine Q_OBJECT to declare meta-object members as protected, not public.
#undef Q_OBJECT
#define Q_OBJECT \
protected: \
    Q_OBJECT_CHECK \
    static const QMetaObject staticMetaObject; \
    Q_OBJECT_GETSTATICMETAOBJECT \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char*); \
    QT_TR_FUNCTIONS \
    virtual int qt_metacall(QMetaObject::Call, int, void**); \
private:

class MiListObject;
class MiObject;

class MI_CORE_EXPORT MiObjectPrivate
{
public:
    MiObject *q_ptr;

    MiObjectPrivate(MiObject *q)
        :   q_ptr(q)
    {}

    virtual ~MiObjectPrivate()
    {}

    const QObjectList &children() const;
    virtual void addChild(MiObject *child);
    virtual void removeChild(MiObject *child);

    virtual void beginChange(int i);
    virtual void endChange(int i);

    virtual void childChanged(int i)
    {
        endChange(i);
    }
};

class MI_CORE_EXPORT MiObject : protected QObject
{
    Q_OBJECT

public:
    enum PropertyIndex {
        IdIndex = 0,
        PropertyCount
    };

    ~MiObject()
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

    MiObject *parent() const;

    static bool connect(const MiObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType type = Qt::UniqueConnection)
    {
        return QObject::connect(sender, signal, receiver, member, type);
    }

    bool disconnect(const QObject *receiver, const char *member = 0)
    {
        return QObject::disconnect(receiver, member);
    }

    template <typename T> T *cast()
    {
        return qobject_cast<T*>(this);
    }

    template <typename T> T *query() const
    {
        return Aggregation::query<T>(this);
    }

    void addComponent(QObject *component)
    {
        Aggregation::Aggregate *agg = Aggregation::query<Aggregation::Aggregate>(this);
        if (!agg) {
            agg = new Aggregation::Aggregate;
            agg->add(this);
        }
        agg->add(component);
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
    Q_DECLARE_FRIENDS(MiObject)

    friend class MiListObject;
    friend class MiListObjectPrivate;
};

inline const QObjectList &MiObjectPrivate::children() const
{
    return q_ptr->children();
}

inline void MiObjectPrivate::addChild(MiObject *child)
{
    Q_ASSERT(child);
    Q_ASSERT(!MiObjectPrivate::children().contains(child));
    child->setParent(q_ptr);
}

inline void MiObjectPrivate::removeChild(MiObject *child)
{
    Q_ASSERT(child);
    Q_ASSERT(MiObjectPrivate::children().contains(child));
    child->setParent(0);
}

typedef QList<MiObject*> MiObjectList;
Q_DECLARE_METATYPE(MiObjectList)

#endif // MI_OBJECT_H
