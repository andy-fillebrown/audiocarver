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

#ifndef MI_MODELITEM_H
#define MI_MODELITEM_H

#include <mi_imodelitem.h>

class DataObject;

class ModelItem : public IModelItem
{
    DataObject *_aggregator;
    IModelItem *_parent;
    QString _name;

public:
    ModelItem(DataObject *aggregator);

    const DataObject *dataObject() const
    {
        return _aggregator;
    }

    void setParent(IModelItem *parent);

    // IAggregate

    const IAggregator *aggregator() const;

    // IModelItem

    const IModel *model() const;

    const IModelItem *parent() const
    {
        return _parent;
    }

    QString name() const
    {
        return _name;
    }

    int itemCount() const
    {
        return 0;
    }

    int indexOf(const IModelItem *item) const
    {
        Q_UNUSED(item);
        Q_ASSERT(false);
        return -1;
    }

    const IModelItem *itemAt(int index) const
    {
        Q_UNUSED(index);
        Q_ASSERT(false);
        return 0;
    }

    const IModelItem *findItem(int type) const
    {
        Q_UNUSED(type);
        Q_ASSERT(false);
        return 0;
    }

    const IModelItemList *findList(int listType) const
    {
        Q_UNUSED(listType);
        Q_ASSERT(false);
        return 0;
    }

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

    bool setName(const QString &name);
    QVariant data(int role) const;
    bool setData(const QVariant &data, int role);

    Qt::ItemFlags flags() const
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
};

#endif // MI_MODELITEM_H
