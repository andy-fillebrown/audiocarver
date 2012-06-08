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

#ifndef MI_DATABASE_OBJECTLIST_H
#define MI_DATABASE_OBJECTLIST_H

#include "mi_database_object.h"

#include "mi_imodellist.h"

namespace Database {

class MI_CORE_EXPORT ObjectList : public Object
{
    const int _listType;
    QList<IAggregator*> _objects;

public:
    ObjectList(int listType = Mi::UnknownItem)
        :   _listType(listType)
    {}

    IAggregator *init();
    ~ObjectList();

    int listType() const
    {
        return _listType;
    }

    bool contains(const QString &name) const
    {
        const QList<Object*> *objects = this->objects();
        QList<Object*>::ConstIterator end = objects->constEnd();
        for (QList<Object*>::ConstIterator i = objects->constBegin();  i != end;  ++i)
            if ((*i)->name() == name)
                return true;
        return false;
    }

    int count() const
    {
        return _objects.count();
    }

    IAggregator *at(int i) const
    {
        return _objects.at(i);
    }

    void insert(int i, Object *object)
    {
        ObjectList *old_list = object->list();
        if (old_list) {
            if (old_list == this)
                return;
            old_list->_objects.removeOne(object);
        }
        const QString name = object->name();
        if (!name.isEmpty()) {
            int suffix = 0;
            QString new_name = name;
            while (contains(new_name))
                new_name = QString("%1.%2").arg(name).arg(++suffix);
            if (name != new_name)
                object->setName(new_name);
        }
        _objects.insert(i, object);
        object->setParent(this);
    }

    // Object
    bool isList() const
    {
        return true;
    }

protected:
    QList<Object*> *objects()
    {
        return reinterpret_cast<QList<Object*>*>(&_objects);
    }

    const QList<Object*> *objects() const
    {
        return reinterpret_cast<const QList<Object*>*>(&_objects);
    }

    class ModelList : public IModelList
    {
        ObjectList *_aggregator;

    public:
        ModelList(ObjectList *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

    protected:
        ObjectList *a() const
        {
            return _aggregator;
        }

        // IModelList
        int listType() const
        {
            return a()->listType();
        }

        bool containsObjectNamed(const QString &name) const
        {
            return a()->contains(name);
        }

        void insert(int i, IModelItem *item)
        {
            a()->insert(i, dynamic_cast<Object*>(query<IAggregator>(item)));
        }

        void removeAt(int i)
        {
            QList<Object*> *objects = a()->objects();
            Object *object = objects->at(i);
            object->setParent(0);
            objects->removeAt(i);
        }

        void clear()
        {
            a()->clear();
        }

        // IModelItem
        int itemType() const
        {
            return Mi::ListItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            return Mi::ListItem == itemType;
        }

        IModelItem *parent() const
        {
            return query<IModelItem>(a()->parent());
        }

        int count() const
        {
            return a()->objects()->count();
        }

        int indexOf(const IModelItem *item) const
        {
            return a()->objects()->indexOf(dynamic_cast<Object*>(item->aggregator()));
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(a()->objects()->at(i));
        }

        IModelItem *findItem(int itemType) const
        {
            Q_ASSERT(0);
            return 0;
        }

        IModelList *findList(int listType) const
        {
            Q_ASSERT(0);
            return 0;
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelList:
            return appendAggregate((new ModelList(this))->init());
        default:
            return 0;
        }
    }

    void clear()
    {
        QList<Object*> *objects = this->objects();
        QList<Object*>::ConstIterator end = objects->end();
        for (QList<Object*>::ConstIterator i = objects->begin();  i != end;  ++i) {
            Object *object = *i;
            object->setParent(0);
            delete object;
        }
        _objects.clear();
    }
};

} // namespace Database

#endif // MI_DATABASE_OBJECTLIST_H
