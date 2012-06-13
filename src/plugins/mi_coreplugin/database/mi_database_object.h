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

#ifndef MI_DATABASE_OBJECT_H
#define MI_DATABASE_OBJECT_H

#include "mi_aggregator.h"

#include "mi_imodeldata.h"
#include "mi_imodelitem.h"

class IModelDataWatcher;
class IModelItemWatcher;

namespace Database {

class ObjectList;

class MI_CORE_EXPORT Object : public Aggregator
{
    friend class ObjectList;
    friend class ScopedDataChange;
    friend class ScopedParentChange;

    enum { RoleCount = 1 };
    enum { ItemCount = 0 };

    QString _name;

    Object *_parent;

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount,
        ItemCountOffset = 0,
        TotalItemCount = ItemCount
    };

    Object()
        :   _parent(0)
    {}

    virtual IAggregator *init();

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

    Object *parent() const
    {
        if (isList() && _parent)
            return _parent->parent();
        else
            return _parent;
    }

    void setParent(Object *parent);

    virtual bool isList() const
    {
        return false;
    }

    ObjectList *list() const;

    class MI_CORE_EXPORT ModelData : public IModelData
    {
        Object *_aggregator;
        IModelItem *_item;

    protected:
        ModelData(Object *aggregator)
            :   _aggregator(aggregator)
            ,   _item(0)
        {}

        virtual IAggregate *init();

        Object *a() const
        {
            return _aggregator;
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
            return Mi::NameRole;
        }

        Qt::ItemFlags flags() const
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Qt::DisplayRole:
            case Mi::NameRole:
                return a()->name();
            default:
                Q_ASSERT(0);
                return QVariant();
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Qt::EditRole:
            case Mi::NameRole:
                return a()->setName(qvariant_cast<QString>(data));
            default:
                Q_ASSERT(0);
                return false;
            }
        }

        QList<IModelDataWatcher*> *watchers() const
        {
            return 0;
        }

        void appendWatcher(IModelDataWatcher *watcher)
        {
            Q_ASSERT(0);
        }

        void removeWatcher(IModelDataWatcher *watcher)
        {
            Q_ASSERT(0);
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    class MI_CORE_EXPORT ModelItem : public IModelItem
    {
        IAggregator *_aggregator;

    protected:
        ModelItem(Object *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        Object *a() const
        {
            return static_cast<Object*>(_aggregator);
        }

        // IModelItem
        int itemType() const
        {
            return Mi::UnknownItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            return Mi::UnknownItem == itemType;
        }

        IModelItem *parent() const
        {
            return query<IModelItem>(a()->parent());
        }

        void setParent(IModelItem *parent)
        {
            a()->setParent(dynamic_cast<Object*>(query<IAggregator>(parent)));
        }

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

        QList<IModelItemWatcher*> *watchers() const
        {
            return 0;
        }

        void appendWatcher(IModelItemWatcher *watcher)
        {
            Q_ASSERT(0);
        }

        void removeWatcher(IModelItemWatcher *watcher)
        {
            Q_ASSERT(0);
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };
};

} // namespace Database

#endif // MI_DATABASE_OBJECT_H
