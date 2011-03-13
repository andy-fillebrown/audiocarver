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

#ifndef GEOMETRY_MATRIX_H
#define GEOMETRY_MATRIX_H

#include <gmtl/Matrix.h>

#include <geometry/geometry_global.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Matrix<real, 4, 4> MatrixData;

class Helper;

} // namespace Internal

class GEOMETRY_EXPORT Matrix
{
public:
    Matrix();
    ~Matrix();

private:
    Internal::MatrixData d;

    Matrix(const Internal::MatrixData &d) : d(d) {}

    friend class AxisAlignedBox;
    friend class Frustum;
    friend class LineSegment;
    friend class Plane;
    friend class Ray;
    friend class Sphere;

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_MATRIX_H
