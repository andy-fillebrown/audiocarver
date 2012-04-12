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

#include "mi_scopedchange.h"

#include <mi_dataobject.h>
#include <mi_imodel.h>

ScopedChange::ScopedChange(const DataObject *dataObject, int role)
    :   _modelData(query<IModelData>(dataObject))
    ,   _role(role)
{
    IModel *model = IModel::instance();
    if (model)
        model->beginChange(_modelData, _role);
}

ScopedChange::~ScopedChange()
{
    IModel *model = IModel::instance();
    if (model)
        model->endChange(_modelData, _role);
}
