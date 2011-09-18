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

#ifndef ACPOINT_H
#define ACPOINT_H

#include <accoreenums.h>
#include <accoreglobal.h>

#include <QList>
#include <QMetaType>
#include <QPointF>

class Point
{
public:
    Point(CurveType curveType = NoCurve)
        :   curveType(curveType)
    {}

    Point(qreal x, qreal y, CurveType curveType = NoCurve)
        :   pos(x, y)
        ,   curveType(curveType)
    {}

    Point(const QPointF &pos, CurveType curveType = NoCurve)
        :   pos(pos)
        ,   curveType(curveType)
    {}

    bool operator<(const Point &other) const
    {
        if (pos.x() < other.pos.x())
            return true;
        if (other.pos.x() < pos.x())
            return false;
        if (pos.y() < other.pos.y())
            return true;
        return false;
    }

    QPointF pos;
    CurveType curveType;
};

inline bool operator==(const Point &a, const Point &b)
{
    return (a.pos == b.pos && a.curveType == b.curveType);
}

typedef QList<Point> PointList;
Q_DECLARE_METATYPE(PointList);

#endif // ACPOINT_H
