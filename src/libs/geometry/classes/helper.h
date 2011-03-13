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

#include <geometry/classes/linesegment.h>
#include <geometry/classes/plane.h>
#include <geometry/classes/ray.h>

#include <gmtl/Intersection.h>

namespace Geometry {
namespace Internal {

class Helper
{
public:
    inline static Point intersection(const LineSegment &lineSegment, const Plane &plane, bool *isValid = 0)
    {
        real t = 0.0;
        bool ok = gmtl::intersect(plane.d, lineSegment.d, t);
        if (isValid)
            *isValid = ok;

        return Point(lineSegment.d.mOrigin + lineSegment.d.mDir * t);
    }
};

} // namespace Internal
} // namespace Geometry

#endif // GEOMETRY_HELPER_H
