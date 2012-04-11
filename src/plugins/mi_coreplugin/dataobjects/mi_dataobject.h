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

    Q_DECLARE_BASE_ROLECOUNT(1)
    QString _name;

    enum { TotalItemCount = 0 };

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
        Q_DECLARE_BASE_MODELDATA
        Q_DECLARE_BASE_MODELDATA_FUNCTIONS

        // IModelData

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
                return a()->setName(qvariant_cast<QString>(data));
            default:
                Q_ASSERT(false);
                return false;
            }
        }
    };

    class ModelItem : public IModelItem
    {
        Q_DECLARE_BASE_MODELITEM
        Q_DECLARE_BASE_MODELITEM_ITEMTYPE(Mi::UnknownItem)

        // IModelItem

        IModelItem *parent() const
        {
            return query<IModelItem>(a()->parent());
        }

        int count() const { return 0; }
        int indexOf(IModelItem*) const { return -1; }
        IModelItem *at(int) const { return 0; }
        IModelItem *findItem(int) const { return 0; }
        IModelList *findList(int) const { return 0; }
    };
};

#endif // MI_DATAOBJECT_H
