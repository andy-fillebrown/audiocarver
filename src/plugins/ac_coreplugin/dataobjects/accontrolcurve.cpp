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

#include <acscoreobject.h>

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
        if (points.count() < 2) {
            points.clear();
            points.append(Point(0.0f, 0.0f));
            points.append(Point(1.0f, 0.0f));
        } else {
            qSort(points);
            points.first().pos = QPointF();
            points.last().pos.rx() = 1.0f;
            int n = 0;
            for (int i = 0;  i < n;  ++i) {
                Point &pt = points[i];
                pt.pos.rx() = qBound(qreal(0.0f), pt.pos.x(), qreal(1.0f));
                pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(1.0f));
            }
        }
    }

    void updateGraphicsParent()
    {
        Q_Q(ControlCurve);
        ScoreObject *graphicsParent = q->graphicsParent();
        graphicsCurveItem->setParentItem(
                    graphicsParent ?
                        graphicsParent->d_func()->mainGraphicsItems[Ac::ControlScene]
                      : 0);
    }
};

ControlCurve::ControlCurve(QObject *parent)
    :   Curve(*(new ControlCurvePrivate(this)), parent)
{
    Q_D(ControlCurve);
    d->updateGraphicsParent();
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
    d->beginChangeData();
    d->controlId = controlId;
    d->endChangeData();
}

ScoreObject *ControlCurve::graphicsParent() const
{
    QObject *parent = QObject::parent();
    return parent ? qobject_cast<ScoreObject*>(parent->parent()) : 0;
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
