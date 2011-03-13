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

#ifndef GEOMETRY_QUATERNIONCOORD_H
#define GEOMETRY_QUATERNIONCOORD_H

#include <gmtl/Coord.h>

#include <geometry/geometry_global.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Coord<gmtl::Vec<real, 3>, gmtl::Quat<real> > QuaternionCoordData;

class Helper;

} // namespace Internal

class GEOMETRY_EXPORT QuaternionCoord
{
public:
    QuaternionCoord() {}
    ~QuaternionCoord() {}

private:
    Internal::QuaternionCoordData d;

    QuaternionCoord(const Internal::QuaternionCoordData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_QUATERNIONCOORD_H
