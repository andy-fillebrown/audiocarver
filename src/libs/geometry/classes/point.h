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

#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include <gmtl/Point.h>

#include <geometry/geometry_global.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Point<real, 3> PointData;
class Helper;

} // namespace Internal

class AxisAlignedBox;
class Sphere;

class GEOMETRY_EXPORT Point
{
public:
    Point(real x = 0.0, real y = 0.0, real z = 0.0) :   d(x, y, z) {}
    ~Point() {}

    real x() const { return d[0]; }
    void setX(real x) { d[0] = x; }

    real y() const { return d[1]; }
    void setY(real y) { d[1] = y; }

    real z() const { return d[2]; }
    void setZ(real z) { d[2] = z; }

    bool isOn(const Sphere &sphere, real tolerance = 0.0) const;

private:
    Internal::PointData d;

    Point(const Internal::PointData &d) : d(d) {}

    friend class Internal::Helper;

    friend class AxisAlignedBox;
    friend class LineSegment;
    friend class Plane;
    friend class Ray;
    friend class Sphere;
};

} // namespace Geometry

#endif // GEOMETRY_POINT_H
