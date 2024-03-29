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

#ifndef MI_CORE_OBJECT_MODELITEM_H
#define MI_CORE_OBJECT_MODELITEM_H

#include "mi_core_base_modelitem.h"

namespace Object {

class Aggregate;

class MI_CORE_EXPORT ModelItem : public Base::ModelItem
{
    QString _name;
    enum { RoleCount = 1 };

    enum { ItemCount = 0 };

public:
    ModelItem(IAggregate *aggregate)
        :   Base::ModelItem(aggregate)
    {}

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount,
        ItemCountOffset = 0,
        TotalItemCount = ItemCount
    };

    Aggregate *aggregate() const;

    int itemType() const;

    bool isTypeOfItem(int itemType) const
    {
        return false;
    }

    IModelItem *parent() const;
    void setParent(IModelItem *parent);

    bool containsItem(IModelItem *item) const
    {
        return false;
    }

    bool containsItemNamed(const QString &name) const
    {
        return false;
    }

    int itemCount() const
    {
        return 0;
    }

    int indexOfItem(const IModelItem *item) const
    {
        return -1;
    }

    IModelItem *itemAt(int i) const
    {
        Q_ASSERT(false);
        return 0;
    }

    void insertItem(int i, IModelItem *item)
    {}

    void removeItemAt(int i)
    {}

    int roleCount() const;
    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(int role, const QVariant &value);
};

}

#endif
