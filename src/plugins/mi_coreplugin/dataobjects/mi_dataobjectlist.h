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

#ifndef MI_DATAOBJECTLIST_H
#define MI_DATAOBJECTLIST_H

#include "mi_dataobject.h"
#include "mi_imodellist.h"

class DataObject;

typedef QList<DataObject*> DataObjects;

class MI_CORE_EXPORT DataObjectList : public DataObject
{
    Q_I_DERIVED__AGGREGATOR(DataObjectList, DataObject)
    const int _listType;
    DataObjects _list;

protected:
    DataObjectList(int listType = Mi::UnknownItem)
        :   _listType(listType)
    {}

public:
    int listType() const
    {
        return _listType;
    }

protected:
    DataObjects &list()
    {
        return _list;
    }

    // IAggregator

    void *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelList:
            return Q_I_CREATE__AGGREGATE(ModelList);
        default:
            return 0;
        }
    }

    class ModelList : public IModelList
    {
        Q_I_BASE__MODEL_LIST
        Q_I_BASE__MODEL_ITEM__ITEM_TYPE(Mi::ListItem)
        Q_I_BASE__MODEL_ITEM__PARENT

        // IModelList

        int listType() const
        {
            return a()->listType();
        }

        bool has(const QString &name) const
        {
            DataObjects &list = a()->list();
            DataObjects::ConstIterator end = list.constEnd();
            for (DataObjects::ConstIterator i = list.constBegin();  i != end;  ++i)
                if ((*i)->name() == name)
                    return true;
            return false;
        }

        void insert(int i, IModelItem *item)
        {
            DataObject *item_a = cast<DataObject>(item->aggregator());
            IModelList *old_item_list = item->list();
            if (old_item_list)
                old_item_list->remove(item);
            IModelData *item_data = query<IModelData>(item->aggregator());
            const QString name = item_data->get<QString>(Mi::NameRole);
            if (!name.isEmpty()) {
                int suffix = 0;
                QString new_name = name;
                while (has(new_name))
                    new_name = QString("%1.%2").arg(name).arg(++suffix);
                if (name != new_name)
                    item_data->set(new_name, Mi::NameRole);
            }
            Q_IA(DataObjectList);
            a->list().insert(i, item_a);
            item_a->setParent(a);
        }

        void removeAt(int i)
        {
            a()->list().removeAt(i);
        }

        void clear()
        {
            DataObjects &list = a()->list();
            qDeleteAll(list);
            list.clear();
        }

        // IModelItem

        int count() const
        {
            return a()->list().count();
        }

        int indexOf(IModelItem *item) const
        {
            return a()->list().indexOf(cast<DataObject>(item->aggregator()));
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(a()->list().at(i));
        }

        IModelItem *findItem(int itemType) const { Q_ASSERT(0); return 0; }
        IModelList *findList(int listType) const { Q_ASSERT(0); return 0; }
    };
};

#endif // MI_DATAOBJECTLIST_H
