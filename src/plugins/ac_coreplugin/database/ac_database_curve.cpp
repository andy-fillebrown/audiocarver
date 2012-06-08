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

#include "ac_database_curve.h"

#include <mi_scopeddatachange.h>

namespace Database {

IAggregator *Curve::init()
{
    static PointList points;
    _pointsStack.push(points);
    return Object::init();
}

void Curve::pushPoints(const PointList &points)
{
    ScopedDataChange data_change(this, Ac::PointsRole, Mi::NotifyParent);
    _pointsStack.push(points);
    conformPoints();
}

void Curve::popPoints()
{
    if (1 == _pointsStack.count())
        return;
    ScopedDataChange data_change(this, Ac::PointsRole, Mi::NotifyParent);
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
    ScopedDataChange data_change(this, Ac::PointsRole, Mi::NotifyModelAndParent);
    _pointsStack.top() = new_pts;
    return true;
}

IAggregate *Curve::Points::init()
{
    return this;
}

IAggregate *Curve::ModelData::init()
{
    return Object::ModelData::init();
}

IAggregate *Curve::ModelItem::init()
{
    return Object::ModelItem::init();
}

} // namespace Database
