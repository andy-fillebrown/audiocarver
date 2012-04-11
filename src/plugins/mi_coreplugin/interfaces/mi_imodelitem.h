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

#ifndef MI_IMODELITEM_H
#define MI_IMODELITEM_H

#include "mi_iaggregate.h"

class IModel;
class IModelList;

class IModelItem : public IAggregate
{
public:
    Q_I_DERIVED__UNKNOWN__INTERFACE_TYPE(IModelItem, IAggregate)

    virtual int itemType() const = 0;
    virtual bool isTypeOfItem(int itemType) const = 0;
    virtual IModelItem *parent() const = 0;
    virtual int count() const = 0;
    virtual int indexOf(IModelItem *item) const = 0;
    virtual IModelItem *at(int i) const = 0;
    virtual IModelItem *findItem(int itemType) const = 0;
    virtual IModelList *findList(int listType) const = 0;

    inline IModelList *list() const;
};

#include <mi_iaggregator.h>
#include <mi_imodellist.h>

inline IModelList *IModelItem::list() const
{
    IModelItem *parent = this->parent();
    return parent ? query<IModelList>(parent->aggregator()) : 0;
}

#endif // MI_IMODELITEM_H
