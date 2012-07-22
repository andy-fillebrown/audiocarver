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

#ifndef MI_CORE_MODEL_H
#define MI_CORE_MODEL_H

#include "mi_imodel.h"

namespace Mi {
namespace Core {

class Database;

class MI_CORE_EXPORT Model : public IModel
{
    static IModel *instance()
    {
        return IModel::instance();
    }

    Database *_aggregator;

protected:
    Database *a() const
    {
        return _aggregator;
    }

    Model(Mi::Core::Database *aggregator);
    virtual IAggregate *init();
    ~Model();

    IAggregator *aggregator() const;
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_MODEL_H
