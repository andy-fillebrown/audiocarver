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

#ifndef AC_GRIPSELECTIONMODEL_H
#define AC_GRIPSELECTIONMODEL_H

#include <QAbstractTableModel>

class IGripItem;

class GripSelectionModelPrivate;
class GripSelectionModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    GripSelectionModel(QObject *parent = 0);
    ~GripSelectionModel();

    static GripSelectionModel *instance();

    // QAbstractItemModel
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
    friend class GraphicsGripItem;
    void appendGrip(IGripItem *grip);
    void removeGrip(IGripItem *grip);
    void update();

    GripSelectionModelPrivate *d;
};

#endif // AC_GRIPSELECTIONMODEL_H
