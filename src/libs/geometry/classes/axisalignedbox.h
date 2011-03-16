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

#ifndef GEOMETRY_AXISALIGNEDBOX_H
#define GEOMETRY_AXISALIGNEDBOX_H

#include <geometry/classes/point.h>
#include <geometry/classes/vector.h>

#include <gmtl/AABox.h>

namespace Geometry {
namespace Internal {

typedef gmtl::AABox<real> AxisAlignedBoxData;

} // namespace Internal

class LineSegment;
class Ray;

class GEOMETRY_EXPORT AxisAlignedBox
{
public:
    AxisAlignedBox() {}
    AxisAlignedBox(const Point &minimumPoint, const Point &maximumPoint) : d(minimumPoint.d, maximumPoint.d) {}
    AxisAlignedBox(const AxisAlignedBox &box) : d(box.d) {}
    ~AxisAlignedBox() {}

    Point minimumPoint() const { return d.mMin; }
    void setMinimumPoint(const Point &point) { d.mMin = point.d; }

    Point maximumPoint() const { return d.mMax; }
    void setMaximumPoint(const Point &point) { d.mMax = point.d; }

    bool contains(const AxisAlignedBox &box) const;
    bool contains(const Point &point) const;
    template <typename ForwardIterator> inline bool contains(ForwardIterator begin, ForwardIterator end) const;
    template <typename Container> inline bool contains(const Container &c) const;

    void expandToContain(const AxisAlignedBox &box);
    void expandToContain(const Point &point);
    template <typename ForwardIterator> inline void expandToContain(ForwardIterator begin, ForwardIterator end) const;
    template <typename Container> inline void expandToContain(const Container &c);

    bool intersectsWith(const AxisAlignedBox &box) const;
    bool intersectsWith(const LineSegment &line) const;
    bool intersectsWith(const Ray &ray) const;

    LineSegment findIntersectionLine(const LineSegment &line, bool *wasFound = 0);
    LineSegment findIntersectionLine(const Ray &ray, bool *wasFound = 0);
    Point findIntersectionPoint(const LineSegment &line, bool *wasFound = 0);
    Point findIntersectionPoint(const Ray &ray, bool *wasFound = 0);

    bool fuzzyCompare(const AxisAlignedBox &box) const;

private:
    Internal::AxisAlignedBoxData d;

    AxisAlignedBox(const Internal::AxisAlignedBoxData &d) : d(d) {}

    friend bool operator==(const AxisAlignedBox &a, const AxisAlignedBox &b);
    friend bool operator!=(const AxisAlignedBox &a, const AxisAlignedBox &b);

    friend class Internal::Helper;
};

inline bool operator==(const AxisAlignedBox &a, const AxisAlignedBox &b)
{
    return a.d == b.d;
}

inline bool operator!=(const AxisAlignedBox &a, const AxisAlignedBox &b)
{
    return a.d != b.d;
}

} // namespace Geometry

#endif // GEOMETRY_AXISALIGNEDBOX_H
