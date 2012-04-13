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

#ifndef MI_DATACHANGE_H
#define MI_DATACHANGE_H

#include <mi_iaggregator.h>
#include <mi_imodel.h>
#include <mi_imodeldata.h>
#include <mi_imodelitem.h>

class DataObject;

class DataChange
{
    const IModelData *_data;
    int _role;
    Mi::NotificationFlags _flags;
    IModel *_model;

public:
    DataChange(const IModelData *data)
        :   _data(data)
        ,   _model(0)
    {}

    void init(int role, Mi::NotificationFlags flags = Mi::NotifyModel)
    {
        _role = role;
        _flags = flags;
        if (!_data)
            return;

        if (Mi::NotifyModel & _flags) {
            _model = IModel::instance();
            if (_model)
                _model->beginChange(_data, _role);
        }
    }

    ~DataChange()
    {
        if (!_data)
            return;

        if (_model)
            _model->endChange(_data, _role);
    }
};

#define Q_DATA_CHANGE(Params) \
    DataChange data_change_notifier(const_query<IModelData>(this)); \
    data_change_notifier.init Params ;

#endif // MI_DATACHANGE_H
