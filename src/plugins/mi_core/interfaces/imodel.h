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

#ifndef IMODEL_H
#define IMODEL_H

#include <QAbstractItemModel>
#include <iunknown.h>
#include "mi_core_global.h"
#include "mi_core_interfaces.h"

class IModelData;
class IModelItem;

class MI_CORE_EXPORT IModel : public QAbstractItemModel
        ,   public IUnknown
{
    Q_OBJECT

public:
    enum { InterfaceType = I::IModel };

    static IModel *instance();

    virtual IModelData *indexData(const QModelIndex &index) const = 0;
    virtual IModelItem *indexItem(const QModelIndex &index) const = 0;
    virtual void beginChangeData(const IModelData *data, int role, int changeType) = 0;
    virtual void endChangeData(const IModelData *data, int role, int changeType) = 0;
    virtual void beginChangeParent(const IModelItem* item) = 0;
    virtual void endChangeParent(const IModelItem *item) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }

    void *queryInterface(int interfaceType) const
    {
        if (isTypeOfInterface(interfaceType))
            return const_cast<IModel*>(this);
        return 0;
    }

signals:
    void dataAboutToBeChanged(const IModelData *data, int role, int changeType);
    void dataChanged(const IModelData *data, int role, int changeType);
    void parentAboutToBeChanged(const IModelItem *item);
    void parentChanged(const IModelItem *item);
};

#endif
