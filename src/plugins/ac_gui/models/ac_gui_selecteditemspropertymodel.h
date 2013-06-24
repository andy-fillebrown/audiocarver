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

#ifndef AC_GUI_SELECTEDITEMSPROPERTYMODEL_H
#define AC_GUI_SELECTEDITEMSPROPERTYMODEL_H

#include <ac_gui_propertymodel.h>

class IModelItem;

class SelectedItemsPropertyModelPrivate;
class SelectedItemsPropertyModel : public PropertyModel
{
    Q_OBJECT

public:
    static SelectedItemsPropertyModel *instance();

    SelectedItemsPropertyModel(QObject *parent = 0);
    ~SelectedItemsPropertyModel();

    int rowCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

public slots:
    void update(IModelItem *item = 0, int role = -1);

private:
    friend class SelectedItemsPropertyModelPrivate;
    SelectedItemsPropertyModelPrivate *d;
};

#endif
