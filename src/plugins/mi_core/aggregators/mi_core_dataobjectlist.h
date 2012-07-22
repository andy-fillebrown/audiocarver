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

    // DataObject
    bool isList() const
    {
        return true;
    }

    class MI_CORE_EXPORT ModelItem : public IModelItem
    {
        friend class DataObjectList;

    protected:
        ModelItem(DataObjectList *aggregator)
            :   IModelItem(aggregator)
        {}

        IAggregate *init();

        DataObjectList *aggregator() const
        {
            return static_cast<DataObjectList*>(IAggregate::aggregator());
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
            return query<IModelItem>(aggregator()->parent());
        }

        void setParent(IModelItem *parent)
        {
            if (!parent) {
                aggregator()->setParent(0);
                return;
            }
            DataObject *parent_aggregator = dynamic_cast<DataObject*>(parent->aggregator());
            aggregator()->setParent(parent_aggregator);
        }

        IModelList *list() const
        {
            return 0;
        }

        int count() const
        {
            return aggregator()->objects().count();
        }

        int indexOf(const IModelItem *item) const
        {
            return aggregator()->objects().indexOf(item->aggregator());
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(aggregator()->objects().at(i));
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
    };

    class MI_CORE_EXPORT ModelList : public IModelList
    {
        friend class DataObjectList;

    protected:
        ModelList(DataObjectList *aggregator)
            :   IModelList(aggregator)
        {}

        IAggregate *init();

        DataObjectList *aggregator() const
        {
            return static_cast<DataObjectList*>(IAggregate::aggregator());
        }

        // IModelList
        int listType() const
        {
            return aggregator()->listType();
        }

        bool containsObjectNamed(const QString &name) const
        {
            return aggregator()->contains(name);
        }

        int count() const
        {
            return query<IModelItem>(aggregator())->count();
        }

        int indexOf(const IModelItem *item) const
        {
            return query<IModelItem>(aggregator())->indexOf(item);
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(aggregator())->at(i);
        }

        void insert(int i, IModelItem *item)
        {
            aggregator()->insert(i, dynamic_cast<DataObject*>(item->aggregator()));
        }

        void removeAt(int i)
        {
            QList<IAggregator*> &objects = aggregator()->objects();
            dynamic_cast<DataObject*>(objects.at(i))->setParent(0);
            objects.removeAt(i);
        }

        void clear()
        {
            aggregator()->clear();
        }
    };

    // IAggregator
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
