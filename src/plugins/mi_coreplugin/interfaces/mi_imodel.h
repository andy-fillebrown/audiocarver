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

#ifndef MI_IMODEL_H
#define MI_IMODEL_H

#include "mi_iaggregate.h"

class IModelData;
class IModelItem;

class MI_CORE_EXPORT IModel : public IAggregate
{
public:
    Q_I_DERIVED__UNKNOWN__INTERFACE_TYPE(IModel, IAggregate)

    IModel();

    static IModel *instance();

    virtual void beginChangeData(const IModelData *data, int role) = 0;
    virtual void endChangeData(const IModelData *data, int role) = 0;
    virtual void beginChangeParent(const IModelItem *item) = 0;
    virtual void endChangeParent(const IModelItem *item) = 0;
};

#endif // MI_IMODEL_H
