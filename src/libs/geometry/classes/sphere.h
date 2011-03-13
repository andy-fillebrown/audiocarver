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

#ifndef GEOMETRY_SPHERE_H
#define GEOMETRY_SPHERE_H

#include <gmtl/Sphere.h>

#include <geometry/classes/point.h>

#include <QtCore/QVector>

namespace Geometry {
namespace Internal {

typedef gmtl::Sphere<real> SphereData;

} // namespace Internal

class GEOMETRY_EXPORT Sphere
{
public:
    Sphere();
    Sphere(const Point &centerPoint, real radius);
    ~Sphere() {}

    static Sphere containing(const QVector<Point> &points);

    bool contains(const Point &point) const;
    bool contains(const QVector<Point> &points) const;
    bool contains(const Sphere &sphere) const;
    bool contains(const QList<Sphere*> &spheres) const;

    void expand(const Point &point);
    void expand(const Sphere &sphere);

private:
    Internal::SphereData d;

    Sphere(const Internal::SphereData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_SPHERE_H
