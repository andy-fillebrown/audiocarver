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

#ifndef GEOMETRY_VECTOR_H
#define GEOMETRY_VECTOR_H

#include <gmtl/Vec.h>

#include <geometry/geometry_global.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Vec<real, 3> VectorData;

class Helper;

} // namespace Internal

class GEOMETRY_EXPORT Vector
{
public:
    Vector(real x, real y, real z);
    ~Vector();

    real x() const;
    void setX(real x);

    real y() const;
    void setY(real y);

    real z() const;
    void setZ(real z);

private:
    Internal::VectorData d;

    Vector(const Internal::VectorData &d) : d(d) {}

    friend class LineSegment;
    friend class Plane;
    friend class Ray;

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_VECTOR_H
