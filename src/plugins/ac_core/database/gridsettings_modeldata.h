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

#ifndef GRIDSETTINGS_MODELDATA_H
#define GRIDSETTINGS_MODELDATA_H

#include <base/modeldata.h>

namespace GridSettings {

class ModelData : public Base::ModelData
{
    int _snapEnabled : 1;
    int _gridSnapEnabled : 1;
    qreal _timeSnap;
    qreal _pitchSnap;
    qreal _controlSnap;
    enum { RoleCount = 5 };

public:
    enum {
        RoleCountOffset = Base::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

protected:
    bool isSnapEnabled() const
    {
        return _snapEnabled;
    }

    bool setSnapEnabled(bool enabled);

    bool isGridSnapEnabled() const
    {
        return _gridSnapEnabled;
    }

    bool setGridSnapEnabled(bool enabled);

    qreal timeSnap() const
    {
        return _timeSnap;
    }

    bool setTimeSnap(qreal snap);

    qreal pitchSnap() const
    {
        return _pitchSnap;
    }

    bool setPitchSnap(qreal snap);

    qreal controlSnap() const
    {
        return _controlSnap;
    }

    bool setControlSnap(qreal snap);

    int roleCount() const
    {
        return TotalRoleCount;
    }

    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}

#endif
