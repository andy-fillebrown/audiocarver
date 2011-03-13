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

#include <gmtl/AABox.h>

#include <geometry/classes/point.h>

namespace Geometry {
namespace Internal {

typedef gmtl::AABox<real> AxisAlignedBoxData;

} // namespace Internal

class GEOMETRY_EXPORT AxisAlignedBox
{
public:
    AxisAlignedBox() {}
    AxisAlignedBox(const Point &minimumPoint, const Point &maximumPoint) : d(minimumPoint.d, maximumPoint.d) {}
    ~AxisAlignedBox() {}

    Point minimumPoint() const { return d.mMin; }
    void setMinimumPoint(const Point &point) { d.mMin = point.d; }

    Point maximumPoint() const { return d.mMax; }
    void setMaximumPoint(const Point &point) { d.mMax = point.d; }

    void expandToContain(const AxisAlignedBox &axisAlignedBox);
    void expandToContain(const Point &point);

    bool contains(const Point &point) const;

    bool intersectsWith(const AxisAlignedBox &axisAlignedBox) const;

private:
    Internal::AxisAlignedBoxData d;

    AxisAlignedBox(const Internal::AxisAlignedBoxData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_AXISALIGNEDBOX_H
