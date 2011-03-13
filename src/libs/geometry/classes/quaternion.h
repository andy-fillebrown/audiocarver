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

#ifndef GEOMETRY_QUATERNION_H
#define GEOMETRY_QUATERNION_H

#include <gmtl/Quat.h>

#include <geometry/geometry_global.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Quat<real> QuaternionData;

class Helper;

} // namespace Internal

class GEOMETRY_EXPORT Quaternion
{
public:
    Quaternion() {}
    ~Quaternion() {}

private:
    Internal::QuaternionData d;

    Quaternion(const Internal::QuaternionData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_QUATERNION_H
