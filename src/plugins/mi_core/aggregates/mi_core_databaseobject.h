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

#ifndef MI_CORE_DATABASEOBJECT_H
#define MI_CORE_DATABASEOBJECT_H

#include "mi_core_aggregate.h"

#include "mi_imodeldata.h"
#include "mi_imodelitem.h"

namespace Mi {
namespace Core {

class DatabaseObjectList;

class MI_CORE_EXPORT DatabaseObject : public Aggregate
{
    friend class DatabaseObjectList;

    enum { RoleCount = 1 };
    enum { ItemCount = 0 };

    QString _name;

    DatabaseObject *_parent;

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount,
        ItemCountOffset = 0,
        TotalItemCount = ItemCount
    };

    DatabaseObject()
    {}

    IAggregate *initialize();

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

    DatabaseObject *parent() const
    {
        if (isList() && _parent)
            return _parent->parent();
        return _parent;
    }

    virtual void setParent(DatabaseObject *parent);

    virtual bool isList() const
    {
        return false;
    }

    DatabaseObjectList *list() const;

    class MI_CORE_EXPORT ModelData : public IModelData
    {
        DatabaseObject *_aggregate;
        IModelItem *_item;

    protected:
        ModelData(DatabaseObject *aggregate)
            :   _aggregate(aggregate)
            ,   _item(0)
        {}

        virtual IUnknown *initialize();

        DatabaseObject *aggregate() const
        {
            return _aggregate;
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

        QVariant getValue(int role) const
        {
            switch (role) {
            case Qt::DisplayRole:
            case NameRole:
                return aggregate()->name();
            default:
                Q_ASSERT(0);
                return QVariant();
            }
        }

        bool setValue(const QVariant &value, int role)
        {
            switch (role) {
            case Qt::EditRole:
            case NameRole:
                return aggregate()->setName(qvariant_cast<QString>(value));
            default:
                Q_ASSERT(0);
                return false;
            }
        }
    };

    class MI_CORE_EXPORT ModelItem : public IModelItem
    {
        DatabaseObject *_aggregate;

    protected:
        ModelItem(DatabaseObject *aggregate)
            :   _aggregate(aggregate)
        {}

        virtual IUnknown *initialize();

        DatabaseObject *aggregate() const
        {
            return _aggregate;
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

        IModelItemList *list() const;

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

        IModelItemList *findList(int listType) const
        {
            return 0;
        }
    };
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_DATABASEOBJECT_H
