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

#ifndef GEOMETRY_PLANE_H
#define GEOMETRY_PLANE_H

#include <gmtl/Plane.h>

#include <geometry/classes/point.h>
#include <geometry/classes/vector.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Plane<real> PlaneData;
class Helper;

} // namespace Internal

class LineSegment;
class Ray;

class GEOMETRY_EXPORT Plane
{
public:
    Plane(const Point &pointOnPlane = Point(), const Vector &normal = Vector()) : d(normal.d, pointOnPlane.d) {}
    ~Plane() {}

    Point intersectionPoint(const LineSegment &lineSegment, bool *isValid = 0) const;
    Point intersectionPoint(const Ray &ray, bool *isValid = 0) const;

private:
    Internal::PlaneData d;

    Plane(const Internal::PlaneData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_PLANE_H
