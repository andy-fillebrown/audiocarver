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

#include "mi_core_databaseobject.h"

#include "mi_imodelitemlist.h"

namespace Mi {
namespace Core {

class MI_CORE_EXPORT DatabaseObjectList : public DatabaseObject
{
    const int _listType;
    QList<IAggregate*> _objects;

protected:
    DatabaseObjectList(int listType = UnknownItem)
        :   _listType(listType)
    {}

    IAggregate *initialize();
    ~DatabaseObjectList();

    int listType() const
    {
        return _listType;
    }

    QList<IAggregate*> &objects()
    {
        return _objects;
    }

    const QList<IAggregate*> &objects() const
    {
        return _objects;
    }

    bool contains(const QString &name) const
    {
        foreach (IAggregate *object, objects())
            if (query<IModelData>(object)->get<QString>(NameRole) == name)
                return true;
        return false;
    }

    int count() const
    {
        return _objects.count();
    }

    IAggregate *at(int i) const
    {
        return _objects.at(i);
    }

    void insert(int i, IAggregate *object)
    {
        IModelItem *item = query<IModelItem>(object);
        IModelItemList *old_list = query<IModelItemList>(item->parent());
        if (old_list) {
            if (old_list == query<IModelItemList>(this))
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
        dynamic_cast<DatabaseObject*>(query<IAggregate>(item))->setParent(this);
    }

    bool isList() const
    {
        return true;
    }

    void clear()
    {
        foreach (IAggregate *object, objects()) {
            dynamic_cast<DatabaseObject*>(object)->setParent(0);
            delete object;
        }
        _objects.clear();
    }

    class MI_CORE_EXPORT ModelItemList : public IModelItemList
    {
        friend class DataObjectList;

        DatabaseObjectList *_aggregate;

    protected:
        ModelItemList(DatabaseObjectList *aggregate)
            :   _aggregate(aggregate)
        {}

        IUnknown *initialize();

        DatabaseObjectList *aggregate() const
        {
            return _aggregate;
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
            return query<IModelItem>(aggregate()->parent());
        }

        void setParent(IModelItem *parent)
        {
            if (!parent) {
                aggregate()->setParent(0);
                return;
            }
            DatabaseObject *parent_aggregate = dynamic_cast<DatabaseObject*>(query<IAggregate>(parent));
            aggregate()->setParent(parent_aggregate);
        }

        IModelItemList *list() const
        {
            return 0;
        }

        int count() const
        {
            return aggregate()->objects().count();
        }

        int indexOf(const IModelItem *item) const
        {
            return aggregate()->objects().indexOf(query<IAggregate>(item));
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(aggregate()->objects().at(i));
        }

        IModelItem *findItem(int itemType) const
        {
            Q_ASSERT(0);
            return 0;
        }

        IModelItemList *findList(int listType) const
        {
            Q_ASSERT(0);
            return 0;
        }

        int listType() const
        {
            return aggregate()->listType();
        }

        bool contains(const QString &name) const
        {
            return aggregate()->contains(name);
        }

        void insert(int i, IModelItem *item)
        {
            aggregate()->insert(i, dynamic_cast<DatabaseObject*>(query<IAggregate>(item)));
        }

        void removeAt(int i)
        {
            QList<IAggregate*> &objects = aggregate()->objects();
            dynamic_cast<DatabaseObject*>(objects.at(i))->setParent(0);
            objects.removeAt(i);
        }

        void clear()
        {
            aggregate()->clear();
        }
    };
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_DATAOBJECTLIST_H
