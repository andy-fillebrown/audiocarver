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
class Helper;

} // namespace Internal

class GEOMETRY_EXPORT AxisAlignedBox
{
public:
    AxisAlignedBox(const Point &minimumPoint = Point(), const Point &maximumPoint = Point(1, 1, 1)) : d(minimumPoint.d, maximumPoint.d) {}
    ~AxisAlignedBox() {}

    Point minimumPoint() const;
    void setMinimumPoint(const Point &point);

    Point maximumPoint() const;
    void setMaximumPoint(const Point &point);

    bool contains(const Point &point) const;

    void expand(const AxisAlignedBox &box);
    void expand(const Point &point);

private:
    Internal::AxisAlignedBoxData d;

    AxisAlignedBox(const Internal::AxisAlignedBoxData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_AXISALIGNEDBOX_H
