/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include <mi_global.h>
#include <mi_namespace.h>

#include <mi_imodelitem.h>

#include <QObject>

#define Q_MI_D(Class) Class##Private * const d = static_cast<Class##Private*>(qGetPtrHelper(q_ptr->d_ptr))
#define Q_MI_Q(Class) Class * const q = static_cast<Class*>(q_ptr);

#define Q_MI_DEFINE_QUERYINTERFACE \
    void *queryInterface(int interface) const \
    { \
        return q_ptr->queryInterface(interface); \
    }

class IModel;

class ObjectPrivate;
class MI_CORE_EXPORT Object : public QObject, public IUnknown
{
    friend class ObjectList;
    friend class ObjectListPrivate;
    friend class UniquelyNamedObject;

    Object()
        :   d_ptr(0)
    {}

    void setParent(QObject *parent)
    {
        QObject::setParent(parent);
    }

    void setObjectName(const QString &name)
    {
        QObject::setObjectName(name);
    }

    Q_OBJECT
    Q_DECLARE_PRIVATE(Object)

protected:
    Object(ObjectPrivate &dd, QObject *parent)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    Object *parent() const
    {
        return object_cast<Object>(QObject::parent());
    }

    const QObjectList &children() const
    {
        return QObject::children();
    }

    inline void *queryInterface(int interface) const;

    QScopedPointer<ObjectPrivate> d_ptr;
};

class MI_CORE_EXPORT ScopedDataChange
{
    ObjectPrivate *d;
    int role;

public:
    inline ScopedDataChange(ObjectPrivate *d, int role);
    inline ~ScopedDataChange();
};

#define Q_SCOPED_DATA_CHANGE(d, role) \
    ScopedDataChange scoped_data_change(qGetPtrHelper(d), role);

class MI_CORE_EXPORT ObjectPrivate
{
    QScopedPointer<IModelItem> _modelItem;

public:
    Object *q_ptr;
    IModel *model;

    class ModelItemHelper
    {
    public:
        Object *q_ptr;

        ModelItemHelper(Object *q)
            :   q_ptr(q)
        {}

        IModelItem *parent() const
        {
            return query<IModelItem>(q_ptr->parent());
        }

        QString name() const
        {
            return q_ptr->objectName();
        }

        void setName(const QString &name)
        {
            if (q_ptr->objectName() == name)
                return;
            Q_MI_D(Object);
            Q_SCOPED_DATA_CHANGE(d, Mi::NameRole);
            q_ptr->setObjectName(name);
        }

        bool hasChild(const QString &name)
        {
            const QString lower_name = name.toLower();
            foreach (QObject *child, q_ptr->children())
                if (child->objectName().toLower() == lower_name)
                    return true;
            return false;
        }

        int roleCount() const
        {
            return q_ptr->metaObject()->propertyCount();
        }

        int roleAt(int i) const
        {
            if (i == 0)
                return Mi::NameRole;
            Q_ASSERT(false);
            return -1;
        }

        Qt::ItemFlags flags() const
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }

        QVariant data(int role) const;
        bool setData(const QVariant &data, int role);
    };

    class ModelItem : public IModelItem
    {
    public:
        Object *q_ptr;
        ModelItemHelper helper;

        ModelItem(Object *q)
            :   q_ptr(q)
            ,   helper(q)
        {}

        IModelItem *parent() const
        {
            return helper.parent();
        }

        QString name() const
        {
            return helper.name();
        }

        void setName(const QString &name)
        {
            helper.setName(name);
        }

        bool hasChild(const QString &name)
        {
            return helper.hasChild(name);
        }

        int count() const
        {
            return 0;
        }

        int indexOf(const IModelItem *item) const
        {
            Q_UNUSED(item);
            Q_ASSERT(false);
            return -1;
        }

        IModelItem *at(int index) const
        {
            Q_UNUSED(index);
            Q_ASSERT(false);
            return 0;
        }

        IModelItem *findItem(int type) const
        {
            Q_UNUSED(type);
            Q_ASSERT(false);
            return 0;
        }

        IModelItemList *findList(int type) const
        {
            Q_UNUSED(type);
            Q_ASSERT(false);
            return 0;
        }

        int roleCount() const
        {
            return helper.roleCount();
        }

        int roleAt(int i) const
        {
            return helper.roleAt(i);
        }

        QVariant data(int role) const
        {
            return helper.data(role);
        }

        bool setData(const QVariant &value, int role)
        {
            return helper.setData(value, role);
        }

        Qt::ItemFlags flags() const
        {
            return helper.flags();
        }

        Q_MI_DEFINE_QUERYINTERFACE
    };

    ObjectPrivate(Object *q, IModelItem *modelItem)
        :   _modelItem(modelItem)
        ,   q_ptr(q)
        ,   model(0)
    {}

    virtual ~ObjectPrivate()
    {}

    IModelItem *modelItem() const
    {
        return qGetPtrHelper(_modelItem);
    }

    virtual void setParent(QObject *parent);
    void clearParent();

    void setModel(IModel *model);
    void beginChangeData(int role);
    void endChangeData(int role);
};

inline void *Object::queryInterface(int interface) const
{
    switch (interface) {
    case Mi::ObjectInterface:
        return interfaceToObject_cast<Object>(this);
    case Mi::ModelItemInterface:
        return d_ptr->modelItem();
    default:
        return 0;
    }
}

inline ScopedDataChange::ScopedDataChange(ObjectPrivate *d, int role)
    :   d(d)
    ,   role(role)
{
    d->beginChangeData(role);
}

inline ScopedDataChange::~ScopedDataChange()
{
    d->endChangeData(role);
}

#endif // MI_OBJECT_H
