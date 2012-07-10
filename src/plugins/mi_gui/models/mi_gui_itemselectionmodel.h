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

#ifndef MI_ITEMSELECTIONMODEL_H
#define MI_ITEMSELECTIONMODEL_H

#include "QItemSelectionModel"

#include <mi_gui_global.h>


class IModelItem;

class MI_GUI_EXPORT ItemSelectionModel : public QItemSelectionModel
{
    Q_OBJECT

public:
    ItemSelectionModel(QAbstractItemModel *model);

    virtual QList<IModelItem*> selectedItems() const;
};

#endif // MI_ITEMSELECTIONMODEL_H
