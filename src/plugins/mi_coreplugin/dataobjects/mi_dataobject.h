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

#ifndef MI_DATAOBJECT_H
#define MI_DATAOBJECT_H

#include <mi_aggregator.h>
#include <mi_imodeldata.h>
#include <mi_imodelitem.h>

class IModel;

class MI_CORE_EXPORT DataObject : public Aggregator
{
    DataObject *_parent;
    QString _name;

protected:
    DataObject()
        :   _parent(0)
    {}

public:
    ~DataObject();

    DataObject *parent() const
    {
        return _parent;
    }

    virtual void setParent(DataObject *parent);

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

protected:

    //-------------------------------------------------------------------------

    class ModelData : public IModelData
    {
        DataObject *_aggregator;

    public:
        ModelData(DataObject *aggregator)
            :   _aggregator(aggregator)
        {}

        DataObject *dataObject() const
        {
            return qGetPtrHelper(_aggregator);
        }

        // IModelData

        int roleCount() const
        {
            return 1;
        }

        int roleAt(int i) const
        {
            switch (i) {
            case 1:
                return Mi::NameRole;
            default:
                Q_ASSERT(false);
                return -1;
            }
        }

        QVariant get(int role) const;
        bool set(const QVariant &data, int role);

        Qt::ItemFlags flags() const
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }

        // IAggregate

        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    //-------------------------------------------------------------------------

    class ModelItem : public IModelItem
    {
        DataObject *_aggregator;

    public:
        ModelItem(DataObject *aggregator)
            :   _aggregator(aggregator)
        {}

        DataObject *dataObject() const
        {
            return qGetPtrHelper(_aggregator);
        }

        // IModelItem

        int itemType() const
        {
            Q_ASSERT(false);
            return Mi::UnknownItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            Q_UNUSED(itemType);
            return false;
        }

        IModelItem *parent() const
        {
            return query<IModelItem>(dataObject()->parent());
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

        IModelItem *at(int i) const
        {
            Q_UNUSED(i);
            Q_ASSERT(false);
            return 0;
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

#endif // MI_DATAOBJECT_H
