/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "accontrolcurve.h"

#include <QVariant>

class ControlCurvePrivate : public CurvePrivate
{
public:
    int controlId;

    ControlCurvePrivate(ControlCurve *q)
        :   CurvePrivate(q)
        ,   controlId(0)
    {}

    void conformPoints()
    {
    }
};

ControlCurve::ControlCurve(QObject *parent)
    :   Curve(*(new ControlCurvePrivate(this)), parent)
{
    setObjectName("ControlCurve");
}

int ControlCurve::controlId() const
{
    Q_D(const ControlCurve);
    return d->controlId;
}

void ControlCurve::setControlId(int controlId)
{
    Q_D(ControlCurve);
    if (d->controlId == controlId)
        return;
    d->controlId = controlId;
}

void ControlCurve::setPoints(const PointList &points)
{
    Q_D(ControlCurve);
    Curve::setPoints(points);
    d->conformPoints();
}

QVariant ControlCurve::data(int role) const
{
    switch (role) {
    case ControlIdRole:
        return controlId();
    default:
        return Curve::data(role);
    }
}

bool ControlCurve::setData(const QVariant &value, int role)
{
    switch (role) {
    case ControlIdRole:
        setControlId(value.toInt());
        return true;
    default:
        return Curve::setData(value, role);
    }
}
