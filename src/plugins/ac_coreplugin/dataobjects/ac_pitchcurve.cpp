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

#include "ac_pitchcurve.h"

#include <ac_note.h>

class PitchCurvePrivate : public CurvePrivate
{
    Q_DECLARE_PUBLIC(PitchCurve)

public:
    PitchCurvePrivate(PitchCurve *q)
        :   CurvePrivate(q)
    {}

    ~PitchCurvePrivate()
    {}

    void conformPoints()
    {
        Q_Q(const PitchCurve);
        PointList points = q->points();
        int n = points.count();
        if (n < 2) {
            points.clear();
            points.append(Point(0.0f, 0.0f));
            points.append(Point(1.0f, 0.0f));
        } else {
            qSort(points);
            for (int i = 0;  i < n;  ++i) {
                Point &pt = points[i];
                pt.pos.rx() = qMax(qreal(0.0f), pt.pos.x());
                pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(127.0f));
            }
        }
        pointsStack.top() = points;
    }

    void updateGraphicsParent()
    {
        GraphicsParentPrivate *parent = graphicsParent();
        graphicsCurveItem->setParentItem(parent ? parent->mainGraphicsItems[Ac::PitchScene] : 0);
    }
};

PitchCurve::PitchCurve(QObject *parent)
    :   Curve(*(new PitchCurvePrivate(this)), parent)
{
    Q_D(PitchCurve);
    d->updateGraphicsParent();
    setName("PitchCurve");
}

ScoreObject *PitchCurve::scoreObject() const
{
    return object_cast<ScoreObject>(QObject::parent());
}

IEntity *PitchCurve::parentEntity() const
{
    return object_cast<Note>(QObject::parent());
}
