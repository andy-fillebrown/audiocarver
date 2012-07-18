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

#ifndef MI_CORE_DATAOBJECTLIST_H
#define MI_CORE_DATAOBJECTLIST_H

#include "mi_core_dataobject.h"

#include "mi_imodellist.h"

namespace Mi {
namespace Core {

class MI_CORE_EXPORT DataObjectList : public DataObject
{
    const int _listType;
    QList<IAggregator*> _objects;

protected:
    DataObjectList(int listType = UnknownItem)
        :   _listType(listType)
    {}

    IAggregator *init();
    ~DataObjectList();

    int listType() const
    {
        return _listType;
    }

    QList<IAggregator*> &objects()
    {
        return _objects;
    }

    const QList<IAggregator*> &objects() const
    {
        return _objects;
    }

    bool contains(const QString &name) const
    {
        foreach (IAggregator *object, objects())
            if (query<IModelData>(object)->get<QString>(NameRole) == name)
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

    void insert(int i, IAggregator *object)
    {
        IModelItem *item = query<IModelItem>(object);
        IModelList *old_list = query<IModelList>(item->parent());
        if (old_list) {
            if (old_list == query<IModelList>(this))
                return;
            old_list->remove(item);
        }
        IModelData *data = query<IModelData>(object);
        const QString name = data->get<QString>(NameRole);
        if (!name.isEmpty()) {
            int suffix = 0;
            QString new_name = name;
            while (contains(new_name))
                new_name = QString("%1.%2").arg(name).arg(++suffix);
            if (name != new_name)
                data->set(new_name, NameRole);
        }
        _objects.insert(i, object);
        dynamic_cast<DataObject*>(item->aggregator())->setParent(this);
    }

    // Object
    bool isList() const
    {
        return true;
    }

    class MI_CORE_EXPORT ModelList : public IModelList
    {
        friend class DataObjectList;

        DataObjectList *_aggregator;

    protected:
        DataObjectList *a() const
        {
            return _aggregator;
        }

        ModelList(DataObjectList *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

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
            a()->insert(i, dynamic_cast<DataObject*>(item->aggregator()));
        }

        void removeAt(int i)
        {
            QList<IAggregator*> &objects = a()->objects();
            dynamic_cast<DataObject*>(objects.at(i))->setParent(0);
            objects.removeAt(i);
        }

        void clear()
        {
            a()->clear();
        }

        // IModelItem
        int itemType() const
        {
            return ListItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            return ListItem == itemType;
        }

        IModelItem *parent() const
        {
            return query<IModelItem>(a()->parent());
        }

        int count() const
        {
            return a()->objects().count();
        }

        int indexOf(const IModelItem *item) const
        {
            return a()->objects().indexOf(item->aggregator());
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(a()->objects().at(i));
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
        foreach (IAggregator *object, objects()) {
            dynamic_cast<DataObject*>(object)->setParent(0);
            delete object;
        }
        _objects.clear();
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_DATAOBJECTLIST_H
