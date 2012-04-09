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

#include <mi_dataobject.h>
#include <mi_imodellist.h>

class DataObject;

typedef QList<DataObject*> DataObjects;

class MI_CORE_EXPORT DataObjectList : public DataObject
{
    const int _listType;
    DataObjects _list;

protected:
    DataObjectList(int listType)
        :   _listType(listType)
    {
        setName(Mi::itemTypeString(_listType) + "s");
    }

    ~DataObjectList();

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
        case Mi::ModelListInterface:
            return appendAggregate(new ModelList(this));
        default:
            return 0;
        }
    }

    //-------------------------------------------------------------------------

    class ModelList : public IModelList
    {
        DataObjectList *_aggregator;

    public:
        ModelList(DataObjectList *aggregator)
            :   _aggregator(aggregator)
        {}

        DataObjectList *dataObject() const
        {
            return qGetPtrHelper(_aggregator);
        }

        // IModelList

        int listType() const
        {
            return dataObject()->listType();
        }

        bool has(const QString &name) const
        {
            DataObjects &list = dataObject()->list();
            DataObjects::ConstIterator end = list.constEnd();
            for (DataObjects::ConstIterator i = list.constBegin();  i != end;  ++i)
                if ((*i)->name() == name)
                    return true;
            return false;
        }

        void insert(int i, IModelItem *item)
        {
            DataObject *object = cast<DataObject>(item->aggregator());
            IModelList *old_list = query<IModelList>(object->parent());
            if (old_list)
                old_list->remove(item);
            IModelData *data = query<IModelData>(item->aggregator());
            const QString name = data->get(Mi::NameRole).toString();
            if (!name.isEmpty()) {
                int suffix = 0;
                QString new_name = name;
                while (has(new_name))
                    new_name = QString("%1.%2").arg(name).arg(++suffix);
                if (name != new_name)
                    data->set(new_name, Mi::NameRole);
            }
            DataObjectList *dataObject = this->dataObject();
            dataObject->list().insert(i, object);
            object->setParent(dataObject);
        }

        void removeAt(int i)
        {
            dataObject()->list().removeAt(i);
        }

        void clear()
        {
            DataObjects &list = dataObject()->list();
            qDeleteAll(list);
            list.clear();
        }

        // IModelItem

        int itemType() const
        {
            Q_ASSERT(false);
            return Mi::UnknownItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            return Mi::ListItem == itemType;
        }

        IModelItem *parent() const
        {
            return query<IModelItem>(dataObject()->parent());
        }

        int count() const
        {
            return dataObject()->list().count();
        }

        int indexOf(IModelItem *item) const
        {
            return dataObject()->list().indexOf(cast<DataObject>(item->aggregator()));
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(dataObject()->list().at(i));
        }

        IModelItem *item(int type) const
        {
            Q_UNUSED(type);
            Q_ASSERT(false);
            return 0;
        }

        IModelList *list(int listType) const
        {
            Q_UNUSED(listType);
            Q_ASSERT(false);
            return 0;
        }

        // IAggregate

        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };
};

#endif // MI_DATAOBJECTLIST_H
