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

class ObjectListPrivate;
class MI_CORE_EXPORT ObjectList : public Object
{
    friend class ModelItemList;

    ObjectList()
    {}

    Q_OBJECT
    Q_DECLARE_PRIVATE(ObjectList)

public:
    enum { Type = Mi::ListItem };

    inline ObjectList(int listType, QObject *parent = 0);

protected:
    inline ObjectList(ObjectListPrivate &dd, QObject *parent);

    inline void *queryInterface(int interface) const;
};

class MI_CORE_EXPORT ScopedItemInsertion
{
    ObjectListPrivate *d;
    int i;

public:
    inline ScopedItemInsertion(ObjectListPrivate *d, int i);
    inline ~ScopedItemInsertion();
};

#define Q_SCOPED_ITEM_INSERTION(d, i) \
    ScopedItemInsertion scoped_item_insertion(qGetPtrHelper(d), i);

class MI_CORE_EXPORT ScopedItemRemoval
{
    ObjectListPrivate *d;
    int i;

public:
    inline ScopedItemRemoval(ObjectListPrivate *d, int i);
    inline ~ScopedItemRemoval();
};

#define Q_SCOPED_ITEM_REMOVAL(d, i) \
    ScopedItemRemoval scoped_item_removal(qGetPtrHelper(d), i);

class ObjectListPrivate : public ObjectPrivate
{
public:
    const int listType;

    class ModelItemList : public IModelItemList
    {
    public:
        ObjectList *q_ptr;
        ObjectPrivate::ModelItemHelper helper;

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

        bool setData(const QVariant &data, int role)
        {
            return helper.setData(data, role);
        }

        Qt::ItemFlags flags() const
        {
            return helper.flags();
        }

        // IModelItemList
        int listType() const
        {
            Q_MI_D(const ObjectList);
            return d->listType;
        }

        void insert(int i, IModelItem *item)
        {
            Object *object = query<Object>(item);
            if (!object)
                return;
            if (q_ptr->children().contains(object))
                return;
            Q_MI_D(ObjectList);
            QObjectList &objects = d->children();
            Q_SCOPED_ITEM_INSERTION(d, i);
            object->d_ptr->setParent(q_ptr);
            if (i != count() - 1) {
                objects.removeLast();
                objects.insert(i, object);
            }
        }

        bool removeAt(int i)
        {
            Object *object = object_cast<Object>(q_ptr->children().at(i));
            if (!object)
                return false;
            Q_MI_D(ObjectList);
            Q_SCOPED_ITEM_REMOVAL(d, i);
            object->d_ptr->clearParent();
            return true;
        }

        void clear()
        {
            if (isEmpty())
                return;
            foreach (QObject *child, q_ptr->children())
                delete child;
        }

        Q_MI_DEFINE_QUERYINTERFACE
        Q_DECLARE_PUBLIC(ObjectList)
    };

    ObjectListPrivate(ObjectList *q, int listType, ModelItemList *modelItemList = 0)
        :   ObjectPrivate(q, modelItemList ? modelItemList : new ModelItemList(q))
        ,   listType(listType)
        ,   _children(0)
    {}

    void init(QObject *q)
    {
        modelItem()->setName(Mi::itemTypeString(listType) + "s");
        _children = &const_cast<QObjectList&>(q->children());
    }

    QObjectList &children()
    {
        return *_children;
    }

    IModelItemList *modelItemList() const
    {
        return interface_cast<IModelItemList>(modelItem());
    }

    void beginInsertItem(int i);
    virtual void endInsertItem(int i);
    void beginRemoveItem(int i);
    virtual void endRemoveItem(int i);

private:
    QObjectList *_children;
};

inline ObjectList::ObjectList(int listType, QObject *parent)
    :   Object(*new ObjectListPrivate(this, listType), parent)
{
    Q_D(ObjectList);
    d->init(this);
}

inline ObjectList::ObjectList(ObjectListPrivate &dd, QObject *parent)
    :   Object(dd, parent)
{
    Q_D(ObjectList);
    d->init(this);
}

inline void *ObjectList::queryInterface(int interface) const
{
    Q_D(const ObjectList);
    switch (interface) {
    case Mi::ModelItemListInterface:
        return d->modelItemList();
    default:
        return Object::queryInterface(interface);
    }
}

inline ScopedItemInsertion::ScopedItemInsertion(ObjectListPrivate *d, int i)
    :   d(d)
    ,   i(i)
{
    d->beginInsertItem(i);
}

inline ScopedItemInsertion::~ScopedItemInsertion()
{
    d->endInsertItem(i);
}

inline ScopedItemRemoval::ScopedItemRemoval(ObjectListPrivate *d, int i)
    :   d(d)
    ,   i(i)
{
    d->beginRemoveItem(i);
}

inline ScopedItemRemoval::~ScopedItemRemoval()
{
    d->endRemoveItem(i);
}

#endif // MI_OBJECTLIST_H
