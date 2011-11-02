/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "ac_proxymodel.h"

class RolesToColumnsProxyModelHelper : public QSortFilterProxyModel
{
public:
    RolesToColumnsProxyModelHelper(QObject *parent = 0)
        :   QSortFilterProxyModel(parent)
        ,   parentModel(object_cast<RolesToColumnsProxyModel>(parent))
    {}

    int columnCount(const QModelIndex &) const { return parentModel ? parentModel->columnCount(QModelIndex()) : 0; }

    bool filterAcceptsColumn(int, const QModelIndex &) const { return true; }
    bool filterAcceptsRow(int, const QModelIndex &) const { return true; }

    RolesToColumnsProxyModel *parentModel;
};

class RolesToColumnsProxyModelPrivate
{
public:
    RolesToColumnsProxyModel *q;
    RolesToColumnsProxyModelHelper *helper;
    RoleMapList roleMaps;

    RolesToColumnsProxyModelPrivate(RolesToColumnsProxyModel *q)
        :   q(q)
        ,   helper(0)
    {}

    void init()
    {
        helper = new RolesToColumnsProxyModelHelper(q);
    }
};

RolesToColumnsProxyModel::RolesToColumnsProxyModel(QObject *parent)
    :   QSortFilterProxyModel(parent)
    ,   d(new RolesToColumnsProxyModelPrivate(this))
{
    d->init();
    QSortFilterProxyModel::setSourceModel(d->helper);
}

RolesToColumnsProxyModel::~RolesToColumnsProxyModel()
{
    delete d;
}

const RoleMapList &RolesToColumnsProxyModel::roleMaps() const
{
    return d->roleMaps;
}

void RolesToColumnsProxyModel::setRoleMaps(const RoleMapList &roleMaps)
{
    d->roleMaps = roleMaps;
}

void RolesToColumnsProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    d->helper->setSourceModel(sourceModel);
}
