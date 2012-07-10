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

#ifndef MI_CORE_SCOPEDDATACHANGE_H
#define MI_CORE_SCOPEDDATACHANGE_H

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodeldata.h>

namespace Mi {
namespace Core {

class ScopedDataChange
{
    const IModelData *_data;
    const int _role;
    const Mi::DataChangeType _dataChangeType;
    IModel *_model;

public:
    ScopedDataChange(const IAggregator *aggregator, int role, Mi::DataChangeType dataChangeType = Mi::PermanentDataChange)
        :   _data(const_query<IModelData>(aggregator))
        ,   _role(role)
        ,   _dataChangeType(dataChangeType)
        ,   _model(query<IModel>(IDatabase::instance()))
    {
        if (!_data)
            return;
        if (_model)
            _model->beginChangeData(_data, _role, _dataChangeType);
    }

    ~ScopedDataChange()
    {
        if (!_data)
            return;
        if (_model)
            _model->endChangeData(_data, _role, _dataChangeType);
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_SCOPEDDATACHANGE_H
