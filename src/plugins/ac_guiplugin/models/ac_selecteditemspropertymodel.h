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

#ifndef AC_SELECTEDITEMSPROPERTYMODEL_H
#define AC_SELECTEDITEMSPROPERTYMODEL_H

#include <ac_propertymodel.h>

class IModelItem;
class ItemSelectionModel;

class SelectedItemsPropertyModelPrivate;
class SelectedItemsPropertyModel : public PropertyModel
{
    Q_OBJECT

public:
    SelectedItemsPropertyModel(QObject *parent = 0);
    ~SelectedItemsPropertyModel();

    static SelectedItemsPropertyModel *instance();

    void appendSelectionModel(ItemSelectionModel *selectionModel);
    void removeSelectionModel(ItemSelectionModel *selectionModel);

    // QAbstractItemModel
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private slots:
    void update();

private:
    friend class SelectedItemsPropertyModelPrivate;
    SelectedItemsPropertyModelPrivate *d;
};

#endif // AC_SELECTEDITEMSPROPERTYMODEL_H
