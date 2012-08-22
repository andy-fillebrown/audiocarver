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

#include "ac_controlcurve_modeldata.h"
#include "ac_core_namespace.h"
#include <mi_scopeddatachange.h>

using namespace Ac;

namespace ControlCurve {

IUnknown *ModelData::initialize()
{
    return Curve::ModelData::initialize();
}

void ModelData::conformPoints()
{
    PointList &points = this->points();
    qSort(points);
    const int n = points.count();
    if (2 <= n) {
        points.first().pos = QPointF();
        points.last().pos.rx() = 1.0f;
        for (int i = 0;  i < n;  ++i) {
            Point &point = points[i];
            point.pos.rx() = qBound(qreal(0.0f), point.pos.x(), qreal(1.0f));
            point.pos.ry() = qBound(qreal(0.0f), point.pos.y(), qreal(1.0f));
        }
    }
}

bool ModelData::setControlType(int controlType)
{
    if (_controlType == controlType)
        return false;
    ScopedDataChange data_change(this, ControlTypeRole);
    _controlType = controlType;
    return true;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return ControlTypeRole;
    default:
        return Curve::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case ControlTypeRole:
        return controlType();
    default:
        return Curve::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case ControlTypeRole:
        return setControlType(qvariant_cast<int>(value));
    default:
        return Curve::ModelData::setValue(value, role);
    }
}

}
