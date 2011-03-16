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

#ifndef GEOMETRY_RAY_H
#define GEOMETRY_RAY_H

#include <gmtl/Ray.h>

#include <geometry/classes/point.h>
#include <geometry/classes/vector.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Ray<real> RayData;

} // namespace Internal

class LineSegment;

class GEOMETRY_EXPORT Ray
{
public:
    Ray();
    Ray(const Point &startPoint, const Vector &vector);
    ~Ray() {}

    Point intersectPointOf(const LineSegment &lineSegment, bool *isValid = 0) const;
    Point intersectPointOf(const Ray &ray, bool *isValid = 0) const;

private:
    Internal::RayData d;

    Ray(const Internal::RayData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_RAY_H
