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

#include "linesegment.h"

#include <classes/helper.h>
#include <classes/plane.h>

using namespace Geometry;

Point LineSegment::intersectionPoint(const Plane &plane, bool *isValid) const
{
    Q_ASSERT(false && "Not implemented yet.");
    return Point();
}
