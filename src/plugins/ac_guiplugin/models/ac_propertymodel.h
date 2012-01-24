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

#ifndef AC_PROPERTYMODEL_H
#define AC_PROPERTYMODEL_H

#include <QAbstractTableModel>

class IModelItem;
class ItemSelectionModel;

class PropertyModelPrivate;
class PropertyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PropertyModel(QObject *parent = 0);
    ~PropertyModel();

    static PropertyModel *instance();

    void appendSelectionModel(ItemSelectionModel *selectionModel);
    void removeSelectionModel(ItemSelectionModel *selectionModel);

    // QAbstractItemModel
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private slots:
    void update();

private:
    friend class PropertyModelPrivate;
    PropertyModelPrivate *d;
};

#endif // AC_TRACKMODEL_H
