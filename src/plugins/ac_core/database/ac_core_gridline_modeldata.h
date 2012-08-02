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

#ifndef AC_CORE_GRIDLINE_MODELDATA_H
#define AC_CORE_GRIDLINE_MODELDATA_H

#include <mi_core_base_modeldata.h>

namespace GridLine {

class ModelData : public Base::ModelData
{
    qreal _location;
    QString _label;
    int _priority;
    int _color;
    enum { RoleCount = 4 };

protected:
    enum {
        RoleCountOffset = Base::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

    qreal location() const
    {
        return _location;
    }

    bool setLocation(qreal location);

    QString label() const
    {
        return _label;
    }

    bool setLabel(const QString &label);

    int priority() const
    {
        return _priority;
    }

    bool setPriority(int priority);

    int color() const
    {
        return _color;
    }

    bool setColor(int color);

    int roleCount() const
    {
        return TotalRoleCount;
    }

    int roleAt(int i) const;
    QVariant getVariant(int role) const;
    bool setValue(const QVariant &value, int role);
};

}

#endif
