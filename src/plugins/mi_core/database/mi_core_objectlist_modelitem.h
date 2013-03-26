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

#ifndef MI_CORE_OBJECTLIST_MODELITEM_H
#define MI_CORE_OBJECTLIST_MODELITEM_H

#include "mi_core_base_modelitem.h"
#include <QList>

namespace ObjectList {

class Aggregate;

class MI_CORE_EXPORT ModelItem : public Base::ModelItem
{
public:
    ModelItem(IAggregate *aggregate, int listType);

protected:
    Aggregate *aggregate() const;

    int itemType() const;
    bool isTypeOfItem(int itemType) const;
    IModelItem *parent() const;

    void setParent(IModelItem *parent)
    {
        Q_ASSERT(false);
    }

    bool containsItem(IModelItem *item) const;
    bool containsItemNamed(const QString &name) const;
    int itemCount() const;
    int indexOfItem(const IModelItem *item) const;
    IModelItem *itemAt(int i) const;

    IModelItem *findItem(int itemType) const
    {
        Q_ASSERT(0);
        return 0;
    }

    IModelItem *findList(int listType) const
    {
        return 0;
    }

    void insertItem(int i, IModelItem *item);
    void removeItemAt(int i);

    int roleCount() const
    {
        return 0;
    }

    int roleAt(int i) const
    {
        return -1;
    }

    QVariant getValue(int role) const;

    bool setValue(int role, const QVariant &value)
    {
        return false;
    }
};

}

#endif
