/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_GUI_GRIPLIST_TOOLS_H
#define AC_GUI_GRIPLIST_TOOLS_H

#include <ac_core_point.h>
#include <igraphicsgrip.h>
#include <igraphicsgriplist.h>

namespace GripList {

inline PointList toPointList(QList<IGraphicsGrip*> grips)
{
    PointList points;
    foreach (IGraphicsGrip *grip, grips)
        points.append(Point(grip->position(), grip->curveType()));
    return points;
}

inline PointList toPointList(IGraphicsGripList *griplist)
{
    return toPointList(griplist->grips());
}

}

#endif
