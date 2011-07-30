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

#include "ac_curve.h"
#include <ac_curvepoint.h>

const QList<AcCurvePoint*> &AcCurve::children() const
{
    return reinterpret_cast<const QList<AcCurvePoint*>&>(d_ptr->children<AcCurvePoint>());
}

qreal AcCurve::duration() const
{
    const QList<AcCurvePoint*> &pts = children();
    return pts.last()->x() - pts.first()->x();
}

bool AcCurve::isSorted() const
{
    Q_D(const AcCurve);
    return d->isSorted<AcCurvePoint>();
}

void AcCurve::sort()
{
    Q_D(AcCurve);
    d->sort<AcCurvePoint>();
}

void AcCurve::update()
{
    if (isChildChanged()) {
        const QList<AcCurvePoint*> &pts = children();
        AcCurvePoint *startPt = pts.first();
        AcCurvePoint *endPt = pts.last();
        const qreal startX = startPt->x();
        const qreal startPrevX = startPt->previousX();
        const qreal startOffset = startX - startPrevX;
        const qreal endX = endPt->x();
        const qreal endPrevX = endPt->previousX();
        const qreal endOffset = endX - endPrevX;
        const qreal middleStretchFactor = (endPrevX - startPrevX) / (endX - startX);
        for (int i = 1;  i < pts.count() - 1;  ++i) {
            AcCurvePoint *pt = pts[i];
            if (pt->previousX() == pt->x()) {
                switch (pt->stretchType()) {
                case AcCurvePoint::StartStretch:
                    pt->setX(pt->x() + startOffset);
                    break;
                case AcCurvePoint::MiddleStretch:
                    pt->setX(pt->x() + (middleStretchFactor * (pt->x() - startPt->x())));
                    break;
                case AcCurvePoint::EndStretch:
                    pt->setX(pt->x() + endOffset);
                    break;
                default:
                    break;
                }
            }
        }
    }
    MiSortedListObject::update();
}
