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

#include "ac_model.h"

#include <mi_imodelitem.h>

#include <ac_database.h>

namespace Database {

IAggregate *Model::init()
{
    return this;
}

IModelItem *Model::rootItem() const
{
    return query<IModelItem>(a()->score());
}

void Model::beginChangeData(const IModelData *data, int role, Mi::DataChangeType dataChangeType)
{
    qDebug() << Q_FUNC_INFO;
}

void Model::endChangeData(const IModelData *data, int role, Mi::DataChangeType dataChangeType)
{
    qDebug() << Q_FUNC_INFO;
}

void Model::beginChangeParent(const IModelItem *item)
{
    qDebug() << Q_FUNC_INFO;
}

void Model::endChangeParent(const IModelItem *item)
{
    qDebug() << Q_FUNC_INFO;
}

IAggregator *Model::aggregator() const
{
    return _aggregator;
}

} // namespace Database
