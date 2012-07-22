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

#ifndef MI_CORE_QDATAMODEL_H
#define MI_CORE_QDATAMODEL_H

#include "mi_iunknown.h"

#include <QAbstractItemModel>

class IAggregator;

class MI_CORE_EXPORT QModel : public QAbstractItemModel, public IUnknown
{
    Q_OBJECT

    IAggregator *_aggregator;

public:
    enum { InterfaceType = I::QModel };

    static QModel *instance();

    QModel(IAggregator *aggregator);
    ~QModel();

    virtual QObject *init();

    // QAbstractItemModel

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }

    void *queryInterface(int interfaceType);
    const void *queryInterface(int interfaceType) const;
};

#endif // MI_CORE_QDATAMODEL_H
