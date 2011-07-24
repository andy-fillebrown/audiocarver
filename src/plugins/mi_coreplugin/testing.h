
#ifndef TESTING_H
#define TESTING_H

#include <QDebug>
#include <QObject>
#include <QMetaProperty>

#include <aggregate.h>

#define Q_ENABLE_QUERY(Class) friend Class *qobject_cast<Class*>(QObject*);

using namespace Aggregation;

class Component;
class IErase;
class IParent;

class Object : protected QObject
{
    Q_OBJECT
    Q_ENABLE_QUERY(Object)

    friend class Component;

public:
    Object();

    virtual bool addChild(Object *child)
    {
        if (!children().contains(child)) {
            child->setParent(this);
            return true;
        }
        return false;
    }

    int propertyCount() const
    {
        return metaObject()->propertyCount();
    }

    const char *propertyName(int i) const
    {
        return metaObject()->property(i).name();
    }

    QVariant propertyValue(int i) const
    {
        return metaObject()->property(i).read(this);
    }

    // Note that the shorter receiver-less form of connect() doesn't work.
    bool connect(const Object *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType type = Qt::UniqueConnection) const
    {
        return QObject::connect(sender, signal, receiver, member, type);
    }

    void addComponent(Component *i);

    template <typename T>
    T *cast() const
    {
        return cast<T>(const_cast<Object*>(this));
    }

    template <typename T>
    static T *cast(Object *object)
    {
        reinterpret_cast<T*>(0)->qt_check_for_QOBJECT_macro(*reinterpret_cast<T*>(object));
        return static_cast<T*>(reinterpret_cast<T*>(0)->staticMetaObject.cast(object));
    }

    template <typename T>
    T *query() const
    {
        return query<T>(const_cast<Object*>(this));
    }

    template <typename T>
    static T *query(Object *object)
    {
        return Aggregation::query<T>(object);
    }

protected:
    template <typename T>
    const QList<T*> &childrenAs() const
    {
        return reinterpret_cast<const QList<T*>&>(children());
    }

    template <typename T>
    QList<T*> &childrenAs()
    {
        return const_cast<QList<T*>&>(reinterpret_cast<const QList<T*>&>(children()));
    }
};

Q_DECLARE_METATYPE(Object*);

class Component : protected QObject
{
    Q_ENABLE_QUERY(Component)

    friend class Object;

public:
    template <typename T>
    T *query() const
    {
        return Aggregation::query<T>(const_cast<Component*>(this));
    }
};

class IErase : public Component
{
    Q_OBJECT
    Q_ENABLE_QUERY(IErase)

public:
    void test()
    {
        Object *root = query<Object>();
        Q_UNUSED(root);
    }
};

class IParent : public Component
{
    Q_OBJECT
    Q_ENABLE_QUERY(IParent)
};

inline Object::Object()
{
    Aggregate *agg = new Aggregate;
    agg->add(this);
    addComponent(new IErase);
    addComponent(new IParent);

    IErase *iErase = query<IErase>();
    Q_UNUSED(iErase);

    IParent *iParent = query<IParent>();
    Q_UNUSED(iParent);
}

inline void Object::addComponent(Component *i)
{
    Aggregate *agg = query<Aggregate>();
    if (!agg) {
        agg = new Aggregate;
        agg->add(this);
    }
    agg->add(i);
}

class IObjectB : public Component
{
    Q_OBJECT
    Q_ENABLE_QUERY(IObjectB)

public:
    void test();
};

class ObjectB : public Object
{
    Q_OBJECT
    Q_ENABLE_QUERY(ObjectB)

public:
    ObjectB()
    {
        addComponent(new IObjectB);
        IObjectB *iObjectB = query<IObjectB>();
        iObjectB->test();
    }
};

inline void IObjectB::test()
{
    ObjectB *root = query<ObjectB>();
    Q_UNUSED(root);
}

class Child : public Object
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)

    int _value;

public:
    Child()
        :   _value(3)
    {}

    int value() const
    {
        return _value;
    }

    void setValue(int value)
    {
        _value = value;
    }

    void change()
    {
        emit changed();
    }

    virtual bool lessThan(const Child *other) const
    {
        Q_UNUSED(other);
        return false;
    }

signals:
    void changed();
};

class Parent : public Object
{
    Q_OBJECT

public:
    const QList<Child*> &children() const
    {
        return childrenAs<Child>();
    }

    virtual bool addChild(Object *child)
    {
        Child *c = cast<Child>(child);
        if (!c) {
            qDebug() << "Wrong object type:" << qPrintable(QString("%1:%2").arg(__FILE__).arg(__LINE__));  Q_ASSERT(false);
            return false;
        }
        if (Object::addChild(child)) {
            sortChildren();
            return c->connect(c, SIGNAL(changed()), this, SLOT(childChanged()));
        }
        return false;
    }

public slots:
    void childChanged()
    {
        qDebug() << "child changed!";
    }

private:
    void sortChildren()
    {
        QList<Child*> &c = childrenAs<Child>();
        qSort(c.begin(), c.end(), lessThan);
    }

    static bool lessThan(const Child *a, const Child *b)
    {
        return a->lessThan(b);
    }
};

class ChildB : public Child
{
    Q_OBJECT
};

class ParentB : public Parent
{
    Q_OBJECT

public:
    const QList<ChildB*> &children() const
    {
        return childrenAs<ChildB>();
    }
};

template <>
inline QObject *Object::cast(Object *object)
{
    qDebug() << "Casting to QObject is not allowed.";
    Q_ASSERT(false);
    return 0;
}

template <>
inline QObject *Object::query() const
{
    qDebug() << "Querying for QObject is not allowed.";
    Q_ASSERT(false);
    return 0;
}

inline void test()
{
    qRegisterMetaType<Object*>();

    Parent *parent = new Parent;
    Child *child = new Child;
    parent->addChild(child);
    child->change();

    ParentB *parentB = new ParentB;
    ChildB *childB = new ChildB;
    parentB->addChild(childB);
    childB->change();

    const QList<ChildB*> &childrenB = parentB->children();
    Q_UNUSED(childrenB);

    parent = parentB;
    const QList<Child*> &children = parent->children();
    Q_UNUSED(children);

    qDebug() << "childB property count ==" << childB->propertyCount();
    qDebug() << "childB property 1 name ==" << childB->propertyName(1);
    qDebug() << "childB property 1 value ==" << childB->propertyValue(1);
}

#endif // TESTING_H
