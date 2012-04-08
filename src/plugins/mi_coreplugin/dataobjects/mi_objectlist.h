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

#ifndef MI_OBJECTLIST_H
#define MI_OBJECTLIST_H

#include <mi_object.h>
#include <mi_imodelitemlist.h>

class ObjectList;
class ObjectListPrivate : public ObjectPrivate
{
public:
    const int listType;

    inline ObjectListPrivate(ObjectList *q, int listType, IModelItemList *modelItemList = 0);

    void init(QObject *q)
    {
        modelItemList_i()->setName(Mi::itemTypeString(listType) + "s");
        _children = &const_cast<QObjectList&>(q->children());
    }

    QObjectList &children()
    {
        return *_children;
    }

    IModelItemList *modelItemList_i() const
    {
        return interface_cast<IModelItemList>(modelItem_i);
    }

    void beginInsertItem(int i);
    virtual void endInsertItem(int i);
    void beginRemoveItem(int i);
    virtual void endRemoveItem(int i);

private:
    QObjectList *_children;
};

class MI_CORE_EXPORT ScopedItemInsertion
{
    ObjectListPrivate *d;
    int i;

public:
    ScopedItemInsertion(ObjectListPrivate *d, int i)
        :   d(d)
        ,   i(i)
    {
        d->beginInsertItem(i);
    }

    ~ScopedItemInsertion()
    {
        d->endInsertItem(i);
    }
};

#define Q_SCOPED_ITEM_INSERTION(d, i) \
    ScopedItemInsertion scoped_item_insertion(qGetPtrHelper(d), i);

class MI_CORE_EXPORT ScopedItemRemoval
{
    ObjectListPrivate *d;
    int i;

public:
    ScopedItemRemoval(ObjectListPrivate *d, int i)
        :   d(d)
        ,   i(i)
    {
        d->beginRemoveItem(i);
    }

    ~ScopedItemRemoval()
    {
        d->endRemoveItem(i);
    }
};

#define Q_SCOPED_ITEM_REMOVAL(d, i) \
    ScopedItemRemoval scoped_item_removal(qGetPtrHelper(d), i);

class MI_CORE_EXPORT ObjectList : public Object
{
    Q_OBJECT

public:
    ObjectList(int listType, QObject *parent = 0)
        :   Object(*new ObjectListPrivate(this, listType), parent)
    {
        Q_D(ObjectList);
        d->init(this);
    }

protected:
    ObjectList(ObjectListPrivate &dd, QObject *parent)
        :   Object(dd, parent)
    {
        Q_D(ObjectList);
        d->init(this);
    }

private:
    ObjectList()
    {}

public:
    enum { Type = Mi::ListItem };

protected:
    void *queryInterface(int interface) const
    {
        Q_D(const ObjectList);
        switch (interface) {
        case Mi::ModelItemListInterface:
            return d->modelItemList_i();
        default:
            return Object::queryInterface(interface);
        }
    }

    class ModelItemList : public IModelItemList
    {
        Q_DECLARE_PUBLIC(ObjectList)

    public:
        ObjectList *q_ptr;
        Object::ModelItemHelper helper;

        ModelItemList(ObjectList *q)
            :   q_ptr(q)
            ,   helper(q)
        {}

        // IModelItem
        int type() const
        {
            return Type;
        }

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
            return q_ptr->children().count();
        }

        int indexOf(const IModelItem *item) const
        {
            return q_ptr->children().indexOf(query<Object>(item));
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(object_cast<Object>(q_ptr->children().at(i)));
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

        QVariant data(int role) const;

        bool setData(const QVariant &value, int role)
        {
            return helper.setData(value, role);
        }

        Qt::ItemFlags flags() const
        {
            return helper.flags();
        }

        // IModelItemList
        int listType() const
        {
            return q_ptr->d_func()->listType;
        }

        void insert(int i, IModelItem *item)
        {
            Q_I_D(ObjectList);
            Object *object = query<Object>(item);
            if (!object)
                return;
            if (q_ptr->children().contains(object))
                return;
            QObjectList &objects = d->children();
            Q_SCOPED_ITEM_INSERTION(d, i);
            query<ObjectPrivate>(object)->setParent(q_ptr);
            if (i != count() - 1) {
                objects.removeLast();
                objects.insert(i, object);
            }
        }

        bool removeAt(int i)
        {
            Q_I_D(ObjectList);
            Object *object = object_cast<Object>(q_ptr->children().at(i));
            if (!object)
                return false;
            Q_SCOPED_ITEM_REMOVAL(d, i);
            query<ObjectPrivate>(object)->clearParent();
            return true;
        }

        void clear()
        {
            if (isEmpty())
                return;
            foreach (QObject *child, q_ptr->children())
                delete child;
        }

        void *queryInterface(int interface) const
        {
            return q_ptr->queryInterface(interface);
        }
    };

private:
    Q_DECLARE_PRIVATE(ObjectList)

    friend class ModelItemList;
};

inline ObjectListPrivate::ObjectListPrivate(ObjectList *q, int listType, IModelItemList *modelItemList)
    :   ObjectPrivate(q, modelItemList ? modelItemList : new ObjectList::ModelItemList(q))
    ,   listType(listType)
    ,   _children(0)
{}

#endif // MI_OBJECTLIST_H
