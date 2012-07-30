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

#include "mi_core_session.qmodel.h"

#include "mi_core_session.aggregate.h"

static QIModel *instance = 0;

QIModel *QIModel::instance()
{
    return ::instance;
}

namespace Mi {
namespace Core {
namespace Session {

QModel::QModel(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    ::instance = this;
}

QModel::~QModel()
{
    ::instance = 0;
}

QObject *QModel::initialize()
{
    aggregate()->append(this);
    return this;
}

IAggregate *QModel::aggregate() const
{
    return _aggregate;
}

QModelIndex QModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex QModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int QModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int QModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant QModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

void *QModel::queryInterface(int interfaceType) const
{
    void *interface = QIModel::queryInterface(interfaceType);
    if (interface)
        return interface;
    return aggregate()->queryInterface(interfaceType);
}

}
}
}
