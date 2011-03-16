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

#ifndef GEOMETRY_SWEPTAXISALIGNEDBOX_H
#define GEOMETRY_SWEPTAXISALIGNEDBOX_H

#include <geometry/classes/axisalignedbox.h>

#include <QtCore/QPair>

namespace Geometry {
namespace Internal {

class SweptAxisAlignedBoxData
{
public:
    AxisAlignedBox box;
    Vector sweep;

    SweptAxisAlignedBoxData(const AxisAlignedBox &box, const Vector &sweep) : box(box), sweep(sweep) {}
};

} // namespace Internal

class GEOMETRY_EXPORT SweptAxisAlignedBox
{
public:
    SweptAxisAlignedBox(const AxisAlignedBox &box, const Vector &sweep) : d(box, sweep) {}
    ~SweptAxisAlignedBox() {}

    AxisAlignedBox &rbox() { return d.box; }
    Vector &rsweep() { return d.sweep; }

    const AxisAlignedBox &box() const { return d.box; }
    void setBox(const AxisAlignedBox &box) { d.box = box; }

    const Vector &sweep() const { return d.sweep; }
    void setSweep(const Vector &sweep) { d.sweep = sweep; }

    bool intersectsWith(const AxisAlignedBox &box) const;
    bool intersectsWith(const SweptAxisAlignedBox &box) const;

    real findFirstIntersectionTime(const AxisAlignedBox &box, bool *wasFound = 0) const;
    real findFirstIntersectionTime(const SweptAxisAlignedBox &box, bool *wasFound = 0) const;
    real findSecondIntersectionTime(const AxisAlignedBox &box, bool *wasFound = 0) const;
    real findSecondIntersectionTime(const SweptAxisAlignedBox &box, bool *wasFound = 0) const;
    QPair<real, real> findIntersectionTimes(const AxisAlignedBox &box, bool *wasFound = 0) const;
    QPair<real, real> findIntersectionTimes(const SweptAxisAlignedBox &box, bool *wasFound = 0) const;

private:
    Internal::SweptAxisAlignedBoxData d;
};

} // namespace Geometry

#endif // GEOMETRY_SWEPTAXISALIGNEDBOX_H
