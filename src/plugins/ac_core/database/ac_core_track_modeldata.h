/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_CORE_TRACK_MODELDATA_H
#define AC_CORE_TRACK_MODELDATA_H

#include "ac_core_scoreobject_modeldata.h"

namespace Track {

class ModelData : public ScoreObject::ModelData
{
    int _color;
    QString _instrument;
    int _visible : 1;
    int _recording : 1;
    enum { RoleCount = 4 };

public:
    ModelData(IAggregate *aggregate);

protected:
    enum {
        RoleCountOffset = ScoreObject::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    bool setColor(int color);
    bool setInstrument(const QString &instrument);
    bool setVisible(bool visible);
    bool setRecording(bool recording);

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
