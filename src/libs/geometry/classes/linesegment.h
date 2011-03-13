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

#ifndef GEOMETRY_LINESEGMENT_H
#define GEOMETRY_LINESEGMENT_H

#include <gmtl/LineSeg.h>

#include <geometry/classes/point.h>
#include <geometry/classes/vector.h>

namespace Geometry {
namespace Internal {

typedef gmtl::LineSeg<real> LineSegmentData;
class Helper;

} // namespace Internal

class Plane;
class Ray;

class GEOMETRY_EXPORT LineSegment
{
public:
    LineSegment(const Point &startPoint, const Point &endPoint) : d(startPoint.d, endPoint.d) {}
    LineSegment(const Point &startPoint, const Vector &vector) : d(startPoint.d, vector.d) {}
    ~LineSegment() {}

    Point intersectionPoint(const LineSegment &lineSegment, bool *isValid = 0) const;
    Point intersectionPoint(const Plane &plane, bool *isValid = 0) const;
    Point intersectionPoint(const Ray &ray, bool *isValid = 0) const;

private:
    Internal::LineSegmentData d;

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_LINESEGMENT_H
