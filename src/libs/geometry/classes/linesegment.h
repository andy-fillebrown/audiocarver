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

namespace Geometry {
namespace Internal {

typedef gmtl::LineSeg<real> LineSegmentData;

} // namespace Internal

class Plane;

class GEOMETRY_EXPORT LineSegment
{
public:
    LineSegment() {}
    LineSegment(const Point &startPoint, const Point &endPoint) : d(startPoint.d, endPoint.d) {}
    ~LineSegment() {}

    Point intersectionPointOf(const Plane &plane, bool *isValid = 0) const;

private:
    LineSegment(const Internal::LineSegmentData &d) : d(d) {}

    Internal::LineSegmentData d;

    friend class AxisAlignedBox;

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_LINESEGMENT_H
