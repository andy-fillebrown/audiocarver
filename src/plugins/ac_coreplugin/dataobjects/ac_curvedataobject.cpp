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

#include "ac_curvedataobject.h"

#include <mi_scopeddatachange.h>

Q_IAGGREGATOR_INIT_ROLES(CurveDataObject) =
{
Ac::PointsRole
};

IAggregator *CurveDataObject::init()
{
    static PointList points;
    _pointsStack.push(points);
    return Base::init();
}

IAggregate *CurveDataObject::Points::init()
{
    return this;
}

IAggregate *CurveDataObject::ModelData::init()
{
    return Base::init();
}

void CurveDataObject::pushPoints(const PointList &points)
{
    Q_SCOPED_DATA_CHANGE((Ac::PointsRole, Mi::NotifyParent))
    _pointsStack.push(points);
}

void CurveDataObject::popPoints()
{
    if (1 == _pointsStack.count())
        return;
    Q_SCOPED_DATA_CHANGE((Ac::PointsRole, Mi::NotifyParent))
    _pointsStack.pop();
}

bool CurveDataObject::setPoints(const PointList &points)
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
    Q_SCOPED_DATA_CHANGE((Ac::PointsRole, Mi::NotifyModelAndParent));
    _pointsStack.top() = new_pts;
    return true;
}
