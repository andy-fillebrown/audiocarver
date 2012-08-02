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

#ifndef MI_CORE_IQMODEL_H
#define MI_CORE_IQMODEL_H

#include <QAbstractItemModel>
#include "mi_core_iunknown.h"

class MI_CORE_EXPORT IQModel : public QAbstractItemModel
        ,   public IUnknown
{
    Q_OBJECT

public:
    enum { InterfaceType = I::IQModel };

    static IQModel *instance();

    IQModel()
    {}

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }

    void *queryInterface(int interfaceType) const
    {
        if (isTypeOfInterface(interfaceType))
            return const_cast<IQModel*>(this);
        return 0;
    }
};

#endif
