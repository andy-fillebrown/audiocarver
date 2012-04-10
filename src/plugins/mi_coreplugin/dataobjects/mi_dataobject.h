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

#include "mi_aggregator.h"
#include "mi_imodeldata.h"
#include "mi_imodelitem.h"

#include <mi_imodel.h>
#include <mi_imodellist.h>
#include <mi_scopedchange.h>

class MI_CORE_EXPORT DataObject : public Aggregator
{
    Q_DECLARE_BASE_AGGREGATOR(DataObject)

    DataObject *_parent;
    QString _name;

protected:
    DataObject()
        :   _parent(0)
    {}

public:
    DataObject *parent() const
    {
        return _parent;
    }

    virtual void setParent(DataObject *parent)
    {
        if (!parent)
            IModel::instance()->orphan(query<IModelItem>(this));
        if (_parent == parent)
            return;
        _parent = parent;
    }

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name)
    {
        if (_name == name)
            return false;
        if (!name.isEmpty()) {
            IModelList *list = query<IModelList>(_parent);
            if (list && list->has(_name))
                return false;
        }
        Q_MI_SCOPED_CHANGE(Mi::NameRole);
        _name = name;
        return true;
    }

protected:
    class ModelData : public IModelData
    {
        Q_DECLARE_BASE_AGGREGATE(ModelData)

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

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Qt::DisplayRole:
            case Mi::NameRole:
                return a()->name();
            default:
                Q_ASSERT(false);
                return QVariant();
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Qt::EditRole:
            case Mi::NameRole:
                return a()->setName(data.toString());
            default:
                Q_ASSERT(false);
                return false;
            }
        }

        Qt::ItemFlags flags() const
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
    };

    class ModelItem : public IModelItem
    {
        Q_DECLARE_BASE_AGGREGATE(ModelItem)

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
            return query<IModelItem>(a()->parent());
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
    };
};

#endif // MI_DATAOBJECT_H
