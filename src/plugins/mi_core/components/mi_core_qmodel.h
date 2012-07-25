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

#ifndef MI_CORE_QMODEL_H
#define MI_CORE_QMODEL_H

#include "mi_qimodel.h"

namespace Mi {
namespace Core {

class Session;

class MI_CORE_EXPORT QModel : public QIModel
{
    Q_OBJECT

public:
    QModel(Session *aggregate);
    ~QModel();
    virtual QObject *initialize();

    Session *aggregate() const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void *queryInterface(int interfaceType) const;
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_MODEL_H
