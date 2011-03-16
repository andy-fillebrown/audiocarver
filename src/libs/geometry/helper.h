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

#ifndef GEOMETRY_HELPER_H
#define GEOMETRY_HELPER_H

//#include <geometry/classes/axisalignedbox.h>
//#include <geometry/classes/frustum.h>
//#include <geometry/classes/linesegment.h>
//#include <geometry/classes/matrix.h>
//#include <geometry/classes/plane.h>
//#include <geometry/classes/ray.h>
//#include <geometry/classes/sphere.h>

//#include <gmtl/Intersection.h>

namespace Geometry {
namespace Internal {

class Helper
{
public:
//    static Point intersectionPointOf(const LineSegment &line, const Plane &plane, bool *isValid = 0)
//    {
//        real t = 0.0;
//        bool valid = gmtl::intersect(plane.d, line.d, t);
//        if (isValid)
//            *isValid = valid;
//        return Point(line.d.mOrigin + line.d.mDir * t);
//    }

//    static Point intersectionPointOf(const Plane &plane, const Ray &ray, bool *isValid = 0)
//    {
//        real t = 0.0;
//        bool valid = gmtl::intersect(plane.d, ray.d, t);
//        if (isValid)
//            *isValid = valid;
//        return Point(ray.d.mOrigin + ray.d.mDir * t);
//    }

//    static LineSegment intersectionLineSegmentOf(const AxisAlignedBox &box, const LineSegment &line, bool *isValid)
//    {
//        unsigned int nHits;
//        real tIn, tOut;
//        bool valid = gmtl::intersect(box.d, line.d, nHits, tIn, tOut);
//        if (isValid)
//            *isValid = valid;
//        if (!valid)
//            return LineSegment();
//        const PointData in = line.d.mOrigin + line.d.mDir * tIn;
//        const PointData out = nHits == 1 ? in : line.d.mOrigin + line.d.mDir * tOut;
//        if (isValid)
//            *isValid = in == out;
//        return LineSegment(LineSegmentData(in, out));
//    }
};

} // namespace Internal
} // namespace Geometry

#endif // GEOMETRY_HELPER_H
