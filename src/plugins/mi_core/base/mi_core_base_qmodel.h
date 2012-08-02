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

#ifndef MI_CORE_BASE_QMODEL_H
#define MI_CORE_BASE_QMODEL_H

#include "mi_core_iqmodel.h"

class IAggregate;

namespace Base {

class MI_CORE_EXPORT QModel : public IQModel
{
    Q_OBJECT

    IAggregate *_aggregate;

public:
    QModel(IAggregate *aggregate);
    ~QModel();
    virtual QObject *initialize();

    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void *queryInterface(int interfaceType) const;
};

}

#endif
