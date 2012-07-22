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

#ifndef MI_CORE_DATAOBJECT_H
#define MI_CORE_DATAOBJECT_H

#include "mi_core_aggregator.h"

#include <mi_imodeldata.h>
#include <mi_imodelitem.h>

namespace Mi {
namespace Core {

class DataObjectList;

class MI_CORE_EXPORT DataObject : public Aggregator
{
    friend class DataObjectList;

    enum { RoleCount = 1 };
    enum { ItemCount = 0 };

    QString _name;

    DataObject *_parent;

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount,
        ItemCountOffset = 0,
        TotalItemCount = ItemCount
    };

    DataObject()
        :   _parent(0)
    {}

    IAggregator *init();

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

    DataObject *parent() const
    {
        if (isList() && _parent)
            return _parent->parent();
        else
            return _parent;
    }

    virtual void setParent(DataObject *parent);

    virtual bool isList() const
    {
        return false;
    }

    DataObjectList *list() const;

    class MI_CORE_EXPORT ModelData : public IModelData
    {
        IModelItem *_item;

    protected:
        ModelData(DataObject *aggregator)
            :   IModelData(aggregator)
            ,   _item(0)
        {}

        IAggregate *init();

        DataObject *aggregator() const
        {
            return static_cast<DataObject*>(IModelData::aggregator());
        }

        // IModelData
        IModelItem *item() const
        {
            return _item;
        }

        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            Q_ASSERT(0 <= i);
            Q_ASSERT(i < RoleCount);
            if (i < 0 || RoleCount <= i)
                return -1;
            return NameRole;
        }

        Qt::ItemFlags flags() const
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Qt::DisplayRole:
            case NameRole:
                return aggregator()->name();
            default:
                Q_ASSERT(0);
                return QVariant();
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Qt::EditRole:
            case NameRole:
                return aggregator()->setName(qvariant_cast<QString>(data));
            default:
                Q_ASSERT(0);
                return false;
            }
        }
    };

    class MI_CORE_EXPORT ModelItem : public IModelItem
    {
    protected:
        ModelItem(DataObject *aggregator)
            :   IModelItem(aggregator)
        {}

        IAggregate *init();

        DataObject *aggregator() const
        {
            return static_cast<DataObject*>(IModelItem::aggregator());
        }

        // IModelItem
        int itemType() const
        {
            return UnknownItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            return UnknownItem == itemType;
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

        IModelList *list() const;

        int count() const
        {
            return 0;
        }

        int indexOf(const IModelItem *item) const
        {
            Q_ASSERT(0);
            return -1;
        }

        IModelItem *at(int i) const
        {
            Q_ASSERT(0);
            return 0;
        }

        IModelItem *findItem(int itemType) const
        {
            return 0;
        }

        IModelList *findList(int listType) const
        {
            return 0;
        }
    };
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_DATAOBJECT_H
