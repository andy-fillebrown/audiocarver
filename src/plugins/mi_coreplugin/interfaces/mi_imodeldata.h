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

#ifndef MI_IMODELDATA_H
#define MI_IMODELDATA_H

#include "mi_iaggregate.h"

class IModelItem;

class QVariant;

class IModelData : public IAggregate
{
public:
    Q_I_DERIVED__UNKNOWN__INTERFACE_TYPE(IModelData, IAggregate)

    virtual IModelItem *item() const = 0;
    virtual int roleCount() const = 0;
    virtual int roleAt(int i) const = 0;
    virtual QVariant getVariant(int role) const = 0;
    virtual bool setVariant(const QVariant &data, int role) = 0;
    virtual Qt::ItemFlags flags() const = 0;

    template <typename T> T get(int role) const
    {
        return getVariant(role).value<T>();
    }

    bool set(const QVariant &data, int role)
    {
        return setVariant(data, role);
    }
};

#endif // MI_IMODELDATA_H
