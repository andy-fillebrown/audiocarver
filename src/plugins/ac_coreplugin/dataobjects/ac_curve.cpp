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

static bool lessThan(const AcPoint *a, const AcPoint *b)
{
    return a->isLessThan(b);
}

AcCurvePrivate::AcCurvePrivate(AcCurvePoint *q)
    :   MiSortedListObjectPrivate(q)
{}

AcCurvePointList &AcCurvePrivate::items()
{
    return MiSortedListObjectPrivate::items<AcCurvePoint>();
}

const AcCurvePointList &AcCurve::items() const
{
    Q_D(const AcCurve);
    return reinterpret_cast<const AcCurvePointList&>(d->children());
}

bool AcCurve::isSorted() const
{
    const AcCurvePointList &items = this->items();
    for (int i = 1;  i < items.count();  ++i)
        if (items[i]->isLessThan(items[i - 1]))
            return false;
    return true;
}

void AcCurve::sort()
{
    if (isSorted())
        return;
    Q_D(AcCurve);
    qSort(d->items(), lessThan);
}

void AcCurve::addItem(MiObject *item)
{
    if (!qobject_cast<AcCurvePoint*>(item))
        return;
    MiSortedListObject::addItem(item);
}

void AcCurve::update()
{
    if (MiObject::ListItemChanged & changedFlags()) {
        Q_D(AcCurve);
        AcCurvePointList &pts = d->items();
        if (2 < pts.count()) {
            AcCurvePoint *startPt = pts.first();
            AcCurvePoint *endPt = pts.last();
            startPt->setCurveType(AcCurvePoint::LinearCurve);
            startPt->setStretchType(AcCurvePoint::StartStretch);
            endPt->setCurveType(AcCurvePoint::LinearCurve);
            endPt->setStretchType(AcCurvePoint::EndStretch);
            const qreal startX = startPt->x();
            const qreal startPrevX = startPt->previousX();
            const qreal endX = endPt->x();
            const qreal endPrevX = endPt->previousX();
            const qreal middleStretchFactor = (endPrevX - startPrevX) / (endX - startX);
            AcCurvePoint::CurveType prevCurveType = AcCurvePoint::LinearCurve;
            for (int i = 1;  i < pts.count() - 1;  ++i) {
                AcCurvePoint *pt = pts[i];
                if (pt->previousX() == pt->x()) {
                    switch (pt->stretchType()) {
                    case AcCurvePoint::StartStretch:
                        pt->setX(pt->x() + startX - startPrevX);
                        break;
                    case AcCurvePoint::MiddleStretch:
                        pt->setX(pt->x() + (middleStretchFactor * (pt->x() - startPt->x())));
                        break;
                    case AcCurvePoint::EndStretch:
                        pt->setX(pt->x() + endX - endPrevX);
                        break;
                    }
                }
                if (AcCurvePoint::BezierCurve == pt->curveType() && AcCurvePoint::BezierCurve == prevCurveType)
                    pt->setCurveType(AcCurvePoint::LinearCurve);
                prevCurveType = pt->curveType();
            }
        }
        foreach (AcCurvePoint *pt, pts)
            pt->update();
    }
    MiSortedListObject::update();
}
