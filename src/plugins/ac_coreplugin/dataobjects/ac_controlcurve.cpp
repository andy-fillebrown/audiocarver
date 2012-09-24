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

#include "ac_controlcurve.h"

#include <ac_note.h>

#include <QVariant>

class ControlCurvePrivate : public CurvePrivate
{
    Q_DECLARE_PUBLIC(ControlCurve)

public:
    int controlId;

    ControlCurvePrivate(ControlCurve *q)
        :   CurvePrivate(q)
        ,   controlId(0)
    {}

    void conformPoints()
    {
        Q_Q(const ControlCurve);
        PointList points = q->points();
        qSort(points);
        const int n = points.count();
        if (2 <= n) {
            points.first().pos = QPointF();
            points.last().pos.rx() = 1.0f;
            for (int i = 0;  i < n;  ++i) {
                Point &pt = points[i];
                pt.pos.rx() = qBound(qreal(0.0f), pt.pos.x(), qreal(1.0f));
                pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(1.0f));
            }
        }
        pointsStack.top() = points;
    }

    void updateGraphicsParent()
    {
        GraphicsParentPrivate *parent = graphicsParent();
        graphicsCurveItem->setParentItem(parent ? parent->mainGraphicsItems[Ac::ControlScene] : 0);
    }
};

ControlCurve::ControlCurve(QObject *parent)
    :   Curve(*(new ControlCurvePrivate(this)), parent)
{
    Q_D(ControlCurve);
    d->updateGraphicsParent();
    setName("ControlCurve");
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
    d->beginChangeData();
    d->controlId = controlId;
    d->endChangeData();
}

ScoreObject *ControlCurve::scoreObject() const
{
    QObject *parent = QObject::parent();
    return parent ? object_cast<ScoreObject>(parent->parent()) : 0;
}

IEntity *ControlCurve::parentEntity() const
{
    QObject *parent = QObject::parent();
    return parent ? object_cast<Note>(parent->parent()) : 0;
}

QVariant ControlCurve::data(int role) const
{
    switch (role) {
    case Ac::ControlIdRole:
        return controlId();
    default:
        return Curve::data(role);
    }
}

bool ControlCurve::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::ControlIdRole:
        setControlId(value.toInt());
        return true;
    default:
        return Curve::setData(value, role);
    }
}
