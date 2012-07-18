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

#include "ac_core_curve.h"

#include <mi_core_scopeddatachange.h>

using namespace Mi;
using namespace Mi::Core;

namespace Ac {
namespace Core {

IAggregator *Curve::init()
{
    static PointList points;
    _pointsStack.push(points);
    return DataObject::init();
}

void Curve::pushPoints(const PointList &points)
{
    ScopedDataChange data_change(this, PointsRole, TemporarayDataChange);
    _pointsStack.push(points);
    conformPoints();
}

void Curve::popPoints()
{
    if (1 == _pointsStack.count())
        return;
    ScopedDataChange data_change(this, PointsRole, TemporarayDataChange);
    _pointsStack.pop();
}

bool Curve::setPoints(const PointList &points)
{
    PointList new_pts = points;
    while (1 < _pointsStack.count())
        _pointsStack.pop();
    PointList old_pts = _pointsStack.top();
    _pointsStack.top() = new_pts;
    conformPoints();
    new_pts = _pointsStack.top();
    _pointsStack.top() = old_pts;
    if (_pointsStack.top() == new_pts)
        return false;
    ScopedDataChange data_change(this, PointsRole);
    _pointsStack.top() = new_pts;
    return true;
}

IAggregate *Curve::Points::init()
{
    return this;
}

IAggregate *Curve::ModelData::init()
{
    return DataObject::ModelData::init();
}

IAggregate *Curve::ModelItem::init()
{
    return DataObject::ModelItem::init();
}

} // namespace Core
} // namespace Ac
