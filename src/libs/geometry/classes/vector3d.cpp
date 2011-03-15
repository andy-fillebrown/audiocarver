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

#include "point2d.h"
#include "point3d.h"
#include "point4d.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"

#include <QtCore/QVariant>

using namespace Geometry;

Vector3D::Vector3D(const Point2D &point)
    :   d(point.d[0], point.d[1], 0.0f)
{
}

Vector3D::Vector3D(const Point3D &point)
    :   d(point.d[0], point.d[1], point.d[2])
{
}

Vector3D::Vector3D(const Point4D &point)
    :   d(point.d[0], point.d[1], point.d[2])
{
}

Vector3D::Vector3D(const Vector2D &vector)
    :   d(vector.d[0], vector.d[1], 0.0f)
{
}

Vector3D::Vector3D(const Vector4D &vector)
    :   d(vector.d[0], vector.d[1], vector.d[2])
{
}

Vector3D::operator QVariant() const
{
    return QVariant(*this);
}
