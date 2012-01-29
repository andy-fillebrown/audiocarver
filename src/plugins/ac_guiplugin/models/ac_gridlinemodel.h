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

#ifndef AC_GRIDLINEMODEL_H
#define AC_GRIDLINEMODEL_H

#include <QAbstractTableModel>

class IModelItem;

class GridLineModelPrivate;
class GridLineModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    GridLineModel(QObject *parent = 0);
    ~GridLineModel();

    void setGridLineType(int type);

    // QAbstractItemModel
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

public slots:
    void apply();

private:
    friend class GridLineModelPrivate;
    GridLineModelPrivate *d;
};

#endif // AC_GRIDLINEMODEL_H
