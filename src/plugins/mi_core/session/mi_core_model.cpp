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

#include "mi_core_model.h"
#include <iaggregate.h>
#include <imodel.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <isession.h>

static IModel *instance = 0;

IModel *IModel::instance()
{
    return ::instance;
}

namespace Base {

Model::Model()
{
    ISession::instance()->remove(::instance);
    delete ::instance;
    ::instance = this;
}

Model::~Model()
{
    ::instance = 0;
}

IUnknown *Model::initialize()
{
    return ISession::instance()->append(this);
}

void *Model::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<Model*>(this);
    return ISession::instance()->queryInterface(interfaceType);
}

void Model::beginChangeData(IModelData *data, int role, int dataChangeType)
{
}

void Model::endChangeData(IModelData *data, int role, int dataChangeType)
{
}

void Model::beginChangeParent(IModelItem *item)
{
}

void Model::endChangeParent(IModelItem *item)
{
}

IModelData *Model::indexData(const QModelIndex &index) const
{
    return query<IModelData>(indexItem(index));
}

IModelItem *Model::indexItem(const QModelIndex &index) const
{
    return static_cast<IModelItem*>(index.internalPointer());
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex Model::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int Model::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    return indexData(index)->getValue(role);
}

}
