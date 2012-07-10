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

#include "mi_gui_itemselectionmodel.h"

#include <mi_imodel.h>
#include <mi_imodelitem.h>

ItemSelectionModel::ItemSelectionModel(QAbstractItemModel *model)
    :   QItemSelectionModel(model)
{}

QList<IModelItem*> ItemSelectionModel::selectedItems() const
{
    QList<IModelItem*> items;

//    IModel *model = IModel::instance();
//    const QModelIndexList indexes = selectedIndexes();

//    const int n = indexes.count();
//    for (int i = 0;  i < n; ++i)
//        items.append(model->item(indexes.at(i)));

    return items;
}
