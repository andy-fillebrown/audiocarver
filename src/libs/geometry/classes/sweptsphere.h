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

#ifndef GEOMETRY_SWEPTSPHERE_H
#define GEOMETRY_SWEPTSPHERE_H

#include <geometry/classes/sphere.h>

#include <geometry/classes/vector.h>

#include <QtCore/QPair>

namespace Geometry {
namespace Internal {

class SweptSphereData
{
public:
    Sphere sphere;
    Vector sweep;

    SweptSphereData(const Sphere &sphere, const Vector &sweep) : sphere(sphere), sweep(sweep) {}
};

} // namespace Internal

class GEOMETRY_EXPORT SweptSphere
{
public:
    SweptSphere(const Sphere &sphere, const Vector &sweep) : d(sphere, sweep) {}
    ~SweptSphere() {}

    const Sphere &sphere() const { return d.sphere; }
    void setSphere(const Sphere &sphere) { d.sphere = sphere; }

    const Vector &sweep() const { return d.sweep; }
    void setSweep(const Vector &sweep) { d.sweep = sweep; }

    bool intersectsWith(const Sphere &sphere) const;
    bool intersectsWith(const SweptSphere &sphere) const;

    real findFirstIntersectionTime(const Sphere &sphere, bool *wasFound = 0) const;
    real findFirstIntersectionTime(const SweptSphere &sphere, bool *wasFound = 0) const;
    real findSecondIntersectionTime(const Sphere &sphere, bool *wasFound = 0) const;
    real findSecondIntersectionTime(const SweptSphere &sphere, bool *wasFound = 0) const;
    QPair<real, real> findIntersectionTimes(const Sphere &sphere, bool *wasFound = 0) const;
    QPair<real, real> findIntersectionTimes(const SweptSphere &sphere, bool *wasFound = 0) const;

private:
    Internal::SweptSphereData d;
};

} // namespace Geometry

#endif // GEOMETRY_SWEPTSPHERE_H
