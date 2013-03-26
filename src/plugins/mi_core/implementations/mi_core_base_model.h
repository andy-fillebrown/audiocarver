/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef MI_CORE_BASE_MODEL_H
#define MI_CORE_BASE_MODEL_H

#include <imodel.h>

namespace Base {

class MI_CORE_EXPORT Model : public IModel
{
public:
    void *queryInterface(int interfaceType) const;
    Model();
    ~Model();

protected:
    void initialize()
    {}

    void beginChangeData(const IModelItem *item, int role);
    void endChangeData(const IModelItem *item, int role);
    void beginInsertItem(const IModelItem *list, int index);
    void endInsertItem(const IModelItem *list, int index);
    void beginRemoveItem(const IModelItem *list, int index);
    void endRemoveItem(const IModelItem *list, int index);
    IModelItem *itemFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromItem(const IModelItem *item) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int columnCount(const QModelIndex &parent) const
    {
        return 1;
    }

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void dataChanged(const IModelItem *item, int role)
    {
        IModel::emit dataChanged(item, role);
    }

    void dataChanged(const QModelIndex &index)
    {
        QAbstractItemModel::emit dataChanged(index, index);
    }
};

}

#endif
