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

#include "ac_pitchcurve.h"

#include <ac_scoreobject.h>

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
        if (points.count() < 2) {
            points.clear();
            points.append(Point(0.0f, 0.0f));
            points.append(Point(1.0f, 0.0f));
        } else {
            qSort(points);
//            points.first().pos = QPointF();
//            points.last().pos.rx() = 1.0f;
            int n = 0;
            for (int i = 0;  i < n;  ++i) {
                Point &pt = points[i];
                pt.pos.rx() = qMax(qreal(0.0f), pt.pos.x());
                pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(127.0f));
            }
        }
    }

    void updateGraphicsParent()
    {
        Q_Q(PitchCurve);
        ScoreObject *graphicsParent = q->graphicsParent();
        graphicsCurveItem->setParentItem(
                    graphicsParent ?
                        graphicsParent->d_func()->mainGraphicsItems[Ac::PitchScene]
                      : 0);
    }
};

PitchCurve::PitchCurve(QObject *parent)
    :   Curve(*(new PitchCurvePrivate(this)), parent)
{
    Q_D(PitchCurve);
    d->updateGraphicsParent();
    setObjectName("PitchCurve");
}

ScoreObject *PitchCurve::graphicsParent() const
{
    QObject *parent = QObject::parent();
    return parent ? qobject_cast<ScoreObject*>(parent) : 0;
}
