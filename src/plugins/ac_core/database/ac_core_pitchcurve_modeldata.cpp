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

#include "ac_core_pitchcurve_modeldata.h"

namespace PitchCurve {

void ModelData::conformPoints()
{
    PointList &points = this->points();
    qSort(points);
    const int n = points.count();
    for (int i = 0;  i < n;  ++i) {
        Point &point = points[i];
        point.pos.rx() = qMax(qreal(0.0f), point.pos.x());
        point.pos.ry() = qBound(qreal(0.0f), point.pos.y(), qreal(127.0f));
    }
}

}
