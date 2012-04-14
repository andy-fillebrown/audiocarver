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

typedef QList<DataObject*> DataObjects;

class MI_CORE_EXPORT DataObjectList : public DataObject
{
    Q_IAGGREGATOR_DERIVED(DataObjectList, DataObject)

    const int _listType;
    AggregatorList _objects;

public:
    DataObjectList(int listType = Mi::UnknownItem)
        :   _listType(listType)
    {}

    ~DataObjectList();

    int listType() const
    {
        return _listType;
    }

    bool containsObjectNamed(const QString &name) const
    {
        const DataObjects &objects = this->objects();
        DataObjects::ConstIterator end = objects.constEnd();
        for (DataObjects::ConstIterator i = objects.constBegin();  i != end;  ++i)
            if ((*i)->name() == name)
                return true;
        return false;
    }

    void insert(int i, DataObject *dataObject)
    {
        DataObjectList *old_list = dataObject->list();
        if (old_list) {
            if (old_list == this)
                return;
            old_list->_objects.removeOne(dataObject);
        }
        const QString name = dataObject->name();
        if (!name.isEmpty()) {
            int suffix = 0;
            QString new_name = name;
            while (containsObjectNamed(new_name))
                new_name = QString("%1.%2").arg(name).arg(++suffix);
            if (name != new_name)
                dataObject->setName(new_name);
        }
        _objects.insert(i, dataObject);
        dataObject->setParent(this);
    }

    void clear()
    {
        DataObjects &objects = this->objects();
        DataObjects::ConstIterator end = objects.end();
        for (DataObjects::ConstIterator i = objects.begin();  i != end;  ++i) {
            DataObject *object = *i;
            object->setParent(0);
            delete object;
        }
        _objects.clear();
    }

    // DataObject
    bool isList() const
    {
        return true;
    }

protected:
    DataObjects &objects()
    {
        return *reinterpret_cast<DataObjects*>(&_objects);
    }

    const DataObjects &objects() const
    {
        return *reinterpret_cast<const DataObjects*>(&_objects);
    }

    // IModelList
    class ModelList : public IModelList
    {
        Q_IMODELLIST_BASE
        Q_IMODELITEM_BASE__ITEMTYPE(Mi::ListItem)

        int listType() const
        {
            return a()->listType();
        }

        bool containsObjectNamed(const QString &name) const
        {
            return a()->containsObjectNamed(name);
        }

        void insert(int i, IModelItem *item)
        {
            a()->insert(i, cast<DataObject>(query<IAggregator>(item)));
        }

        void removeAt(int i)
        {
            DataObjects &a_objects = a()->objects();
            DataObject *dataObject = a_objects.at(i);
            dataObject->setParent(0);
            a_objects.removeAt(i);
        }

        void clear()
        {
            a()->clear();
        }

        // IModelItem
        int count() const
        {
            return a()->objects().count();
        }

        int indexOf(const IModelItem *item) const
        {
            return a()->objects().indexOf(cast<DataObject>(item->aggregator()));
        }

        IModelItem *at(int i) const
        {
            return query<IModelItem>(a()->objects().at(i));
        }

        IModelItem *findItem(int itemType) const { Q_ASSERT(0); return 0; }
        IModelList *findList(int listType) const { Q_ASSERT(0); return 0; }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelList:
            return Q_NEW_AGGREGATE(ModelList);
        default:
            return 0;
        }
    }
};

#endif // MI_DATAOBJECTLIST_H
