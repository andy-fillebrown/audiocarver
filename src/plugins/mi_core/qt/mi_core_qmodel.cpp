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

#include "mi_core_qmodel.h"

#include <mi_iaggregator.h>

static QModel *instance = 0;

QModel *QModel::instance()
{
    return ::instance;
}

QModel::QModel(IAggregator *aggregator)
    :   _aggregator(aggregator)
{
    ::instance = this;
}

QModel::~QModel()
{
    ::instance = 0;
}

QObject *QModel::init()
{
    return this;
}

void *QModel::queryInterface(int interfaceType)
{
    if (isTypeOfInterface(interfaceType))
        return this;
    return _aggregator->queryInterface(interfaceType);
}

const void *QModel::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return this;
    return const_cast<const IAggregator*>(_aggregator)->queryInterface(interfaceType);
}
