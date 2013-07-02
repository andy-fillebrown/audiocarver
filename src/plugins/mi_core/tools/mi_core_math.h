/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef MI_CORE_MATH_H
#define MI_CORE_MATH_H

#include <QPointF>
#include <math.h>

namespace Mi {

inline qreal roundToNearest(const qreal from, const qreal to)
{
    const qreal r = fmod(from, to);
    const qreal td2 = to / qreal(2.0f);
    if (r == 0)
        return from;
    else if (r < td2)
        return from - r;
    else
        return from + (to - r);
}

inline bool isPowerOfTwo(int n)
{
    const int size = 8 * sizeof(int);
    for (int i = 1;  i < size;  i++)
        if (n == (1 << i))
            return true;
    return false;
}

inline int toPowerOfTwo(int n, int min = 4)
{
    if (n < min)
        n = min;
    if (isPowerOfTwo(n))
        return n;
    const int size = 8 * sizeof(int);
    int i = 0;
    for (;  i < size;  i++) {
        if (n == 0) {
            n = 1 << i;
            return n;
        }
        n = n >> 1;
        if (isPowerOfTwo(n)) {
            n = n << (i + 2);
            return n;
        }
    }
    return min;
}

inline qreal intersectionY(const qreal &x1, // start x
                           const qreal &x2, // end x
                           const qreal &y1, // start y
                           const qreal &y2, // end y
                           const qreal &intersectionX)
{
    qreal intY = 0.0;
    if (y1 == y2)
        intY = y1;
    else {
        const qreal x2_x1 = x2 - x1;
        const qreal intX_x1 = intersectionX - x1;
        if ((x2_x1 == 0.0) || (intX_x1 == 0.0))
            intY = y1;
        else
            intY = y1 + (((y2 - y1) / x2_x1) * intX_x1);
    }
    return intY;
}

inline QPointF bezierPoint(const QPointF &pt1, // start point
                           const QPointF &pt2, // control point
                           const QPointF &pt3, // end point
                           const qreal t)
{
    const qreal mu2 = t * t;
    const qreal mum1 = 1 - t;
    const qreal mum12 = mum1 * mum1;
    return QPointF(pt1.x() * mum12 + 2 * pt2.x() * mum1 * t + pt3.x() * mu2,
                   pt1.y() * mum12 + 2 * pt2.y() * mum1 * t + pt3.y() * mu2);
}

}

#endif
