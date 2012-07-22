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

#include "ac_core_model.h"

#include <mi_imodelitem.h>

#include <ac_core_database.h>

namespace Ac {
namespace Core {

Model::Model(Database *aggregator)
    :   Mi::Core::Model(aggregator)
{}

IAggregate *Model::init()
{
    return Mi::Core::Model::init();
}

Database *Model::a() const
{
    return static_cast<Database*>(Mi::Core::Model::a());
}

Mi::Core::QDataModel *Model::q() const
{
    return 0;
}

IModelItem *Model::rootItem() const
{
    return query<IModelItem>(a()->score());
}

//IModelItem *Model::itemFromIndex(const QModelIndex &index) const
//{
//    if ((index.row() < 0)
//            || (index.column() < 0)
//            || (index.model() != query<IQModel>(this)))
//        return rootItem();
//    IModelItem *parent_item = static_cast<IModelItem*>(index.internalPointer());
//    if (!parent_item)
//        return rootItem();
//    return parent_item->at(index.row());
//}

void Model::beginChangeData(const IModelData *data, int role, int dataChangeType)
{
//    qDebug() << Q_FUNC_INFO;
}

void Model::endChangeData(const IModelData *data, int role, int dataChangeType)
{
//    qDebug() << Q_FUNC_INFO;
}

void Model::beginChangeParent(const IModelItem *item)
{
//    qDebug() << Q_FUNC_INFO;
}

void Model::endChangeParent(const IModelItem *item)
{
//    qDebug() << Q_FUNC_INFO;
}

} // namespace Core
} // namespace Ac
