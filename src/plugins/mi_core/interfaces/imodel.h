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

class IModelData;
class IModelItem;
class IModelItemList;

class MI_CORE_EXPORT IModel : public QAbstractItemModel
        ,   public IComponent
{
    Q_OBJECT

public:
    enum { InterfaceType = I::IModel };

    static IModel *instance();

    virtual IModelData *dataFromIndex(const QModelIndex &index) const = 0;
    virtual QModelIndex indexFromData(const IModelData *data) const = 0;
    virtual IModelItem *itemFromIndex(const QModelIndex &index) const = 0;
    virtual QModelIndex indexFromItem(const IModelItem *item) const = 0;
    virtual void beginChangeData(const IModelData *data, int role, int changeType) = 0;
    virtual void endChangeData(const IModelData *data, int role, int changeType) = 0;
    virtual void beginInsertItem(const IModelItemList* list, int index) = 0;
    virtual void endInsertItem(const IModelItemList *list, int index) = 0;
    virtual void beginRemoveItem(const IModelItemList *list, int index) = 0;
    virtual void endRemoveItem(const IModelItemList *list, int index) = 0;

    virtual void reset()
    {
        QAbstractItemModel::reset();
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
    void dataAboutToBeChanged(const IModelData *data, int role, int changeType);
    void dataChanged(const IModelData *data, int role, int changeType);
    void itemAboutToBeInserted(const IModelItemList *list, int index);
    void itemInserted(const IModelItemList *list, int index);
    void itemAboutToBeRemoved(const IModelItemList *list, int index);
    void itemRemoved(const IModelItemList *list, int index);
};

#endif
