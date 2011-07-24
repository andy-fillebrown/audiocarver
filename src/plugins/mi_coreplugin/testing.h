
#include <QDebug>
#include <QObject>
#include <QMetaProperty>

class Object : protected QObject
{
    Q_OBJECT

public:
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

    // Use this instead of qobject_cast<T*>(object)
    template <typename T>
    static T* cast(QObject* object)
    {
#       if !defined(QT_NO_MEMBER_TEMPLATES) && !defined(QT_NO_QOBJECT_CHECK)
            reinterpret_cast<T*>(0)->qt_check_for_QOBJECT_macro(*reinterpret_cast<T*>(object));
#       endif
        return static_cast<T*>(reinterpret_cast<T*>(0)->staticMetaObject.cast(object));
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
            // Note that the shorter receiver-less form of connect() doesn't work.
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

//    parentB->addChild(parent); // should print message and assert

    const QList<ChildB*> &childrenB = parentB->children();
    Q_UNUSED(childrenB);

    parent = parentB;
    const QList<Child*> &children = parent->children();
    Q_UNUSED(children);

    qDebug() << "childB property count ==" << childB->propertyCount();
    qDebug() << "childB property 1 name ==" << childB->propertyName(1);
    qDebug() << "childB property 1 value ==" << childB->propertyValue(1);

    parentB->test();
}
