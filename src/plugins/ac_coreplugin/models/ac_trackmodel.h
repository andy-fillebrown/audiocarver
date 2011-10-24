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

#ifndef AC_TRACKMODEL_H
#define AC_TRACKMODEL_H

#include <ac_global.h>
#include <ac_namespace.h>

#include <QSortFilterProxyModel>

class AC_CORE_EXPORT ColumnExpandingProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ColumnExpandingProxyModel(QObject *parent = 0)
        :   QSortFilterProxyModel(parent)
        ,   _columnCount(3)
    {}

    int columnCount(const QModelIndex &) const { return _columnCount; }
    void setColumnCount(int columnCount) { _columnCount = columnCount; }

    bool filterAcceptsColumn(int, const QModelIndex &) const { return true; }
    bool filterAcceptsRow(int, const QModelIndex &) const { return true; }

private:
    int _columnCount;
};

class AC_CORE_EXPORT TrackModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TrackModel(QObject *parent = 0)
        :   QSortFilterProxyModel(parent)
    {
        ColumnExpandingProxyModel *proxyModel = new ColumnExpandingProxyModel(this);
        proxyModel->setSourceModel(qobject_cast<QAbstractItemModel*>(parent));
        setSourceModel(proxyModel);
    }

    bool filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const
    {
        Q_UNUSED(sourceColumn);
        Q_UNUSED(sourceParent);
        return true;
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
    {
        QAbstractItemModel *m = sourceModel();
        Q_ASSERT(m);
        if (!m)
            return false;
        QModelIndex index = m->index(sourceRow, 0, sourceParent);
        Ac::ItemType type = Ac::ItemType(index.data(Ac::ItemTypeRole).toInt());
        if (Ac::TrackItem == type)
            return true;
        if (Ac::ListItem == type) {
            Ac::ItemType listType = Ac::ItemType(index.data(Ac::ListTypeRole).toInt());
            if (Ac::TrackItem == listType)
                return true;
        }
        return false;
    }

    int columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return 3;
    }

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const
    {
        int col = proxyIndex.column();
        if (0 < col)
            col = 0;
        return QSortFilterProxyModel::mapToSource(createIndex(proxyIndex.row(), 0, proxyIndex.internalPointer()));
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        if (Qt::DisplayRole != role)
            return QSortFilterProxyModel::data(index, role);
        switch (index.column()) {
        case 0:
            return QSortFilterProxyModel::data(index, Ac::ColorRole);
        case 1:
            return QSortFilterProxyModel::data(index, Ac::NameRole);
        case 2:
            return QSortFilterProxyModel::data(index, Ac::VolumeRole);
        default:
            return QSortFilterProxyModel::data(index, role);
        }
    }
};

#endif // AC_MODEL_H
