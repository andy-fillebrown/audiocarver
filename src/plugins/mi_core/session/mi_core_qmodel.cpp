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

#include "qmodel.h"
#include <iaggregate.h>
#include <isession.h>

static IQModel *instance = 0;

IQModel *IQModel::instance()
{
    return ::instance;
}

namespace Base {

QModel::QModel()
{
    ISession::instance()->remove(::instance);
    delete ::instance;
    ::instance = this;
}

QModel::~QModel()
{
    ::instance = 0;
}

IUnknown *QModel::initialize()
{
    return ISession::instance()->append(this);
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
    void *interface = IQModel::queryInterface(interfaceType);
    if (interface)
        return interface;
    return ISession::instance()->queryInterface(interfaceType);
}

}
