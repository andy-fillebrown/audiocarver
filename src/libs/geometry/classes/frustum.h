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

#ifndef GEOMETRY_FRUSTUM_H
#define GEOMETRY_FRUSTUM_H

#include <gmtl/Frustum.h>

#include <geometry/geometry_global.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Frustum<real> FrustumData;
class Helper;

} // namespace Internal

class GEOMETRY_EXPORT Frustum
{
public:
    Frustum() {}
    ~Frustum() {}

private:
    Internal::FrustumData d;

    Frustum(const Internal::FrustumData &d) : d(d) {}

    friend class Internal::Helper;
};

} // namespace Geometry

#endif // GEOMETRY_FRUSTUM_H
