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

#ifndef IMODEL_H
#define IMODEL_H

#include <QAbstractItemModel>
#include <icomponent.h>
#include "mi_core_global.h"

class IModelItem;

class MI_CORE_EXPORT IModel : public QAbstractItemModel
        ,   public IComponent
{
    Q_OBJECT

public:
    enum { InterfaceType = I::IModel };

    static IModel *instance();

    virtual IModelItem *itemFromIndex(const QModelIndex &index) const = 0;
    virtual QModelIndex indexFromItem(IModelItem *item) const = 0;
    virtual void beginChangeData(IModelItem *item, int role) = 0;
    virtual void endChangeData(IModelItem *item, int role) = 0;
    virtual void beginInsertItem(IModelItem* list, int index) = 0;
    virtual void endInsertItem(IModelItem *list, int index) = 0;
    virtual void beginRemoveItem(IModelItem *list, int index) = 0;
    virtual void endRemoveItem(IModelItem *list, int index) = 0;

    virtual void reset()
    {
        QAbstractItemModel::beginResetModel();
        QAbstractItemModel::endResetModel();
    }

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IComponent::isTypeOfInterface(interfaceType);
    }

signals:
    void dataAboutToBeChanged(IModelItem *item, int role);
    void dataChanged(IModelItem *item, int role);
    void itemAboutToBeInserted(IModelItem *list, int index);
    void itemInserted(IModelItem *list, int index);
    void itemAboutToBeRemoved(IModelItem *list, int index);
    void itemRemoved(IModelItem *list, int index);
};

#endif
