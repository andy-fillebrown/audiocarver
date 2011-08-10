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

#ifndef AC_POINT_H
#define AC_POINT_H

#include <ac_core_global.h>
#include <QMetaType>

class AC_CORE_EXPORT AcPoint
{
public:
    enum CurveType {
        NoCurve,
        BezierCurve
    };

    enum StretchType {
        NoStretch,
        StartStretch,
        MiddleStretch,
        EndStretch
    };

    AcPoint(qreal x = 0.0f,
            qreal y = 0.0f,
            CurveType curveType = NoCurve,
            StretchType stretchType = NoStretch)
        :   x(x)
        ,   y(y)
        ,   curveType(curveType)
        ,   stretchType(stretchType)
    {}

    qreal x;
    qreal y;
    CurveType curveType;
    StretchType stretchType;
};

inline bool operator<(const AcPoint &a, const AcPoint &b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

typedef QList<AcPoint> AcPoints;

Q_DECLARE_METATYPE(AcPoint)
Q_DECLARE_METATYPE(AcPoints)

#endif // AC_POINT_H
