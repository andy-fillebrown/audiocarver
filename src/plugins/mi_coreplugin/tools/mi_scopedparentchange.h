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

#ifndef MI_SCOPEDPARENTCHANGE_H
#define MI_SCOPEDPARENTCHANGE_H

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

namespace Database {

class ScopedParentChange
{
    const IModelItem *_item;
    IModel *_model;

public:
    ScopedParentChange(const IAggregator *aggregator)
        :   _item(const_query<IModelItem>(aggregator))
        ,   _model(query<IModel>(IDatabase::instance()))
    {
        if (!_item)
            return;
        if (_model)
            _model->beginChangeParent(_item);
    }

    ~ScopedParentChange()
    {
        if (!_item)
            return;
        if (_model)
            _model->endChangeParent(_item);
    }
};

} // namespace Database

#endif // MI_SCOPEDPARENTCHANGE_H
