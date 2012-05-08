/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef AC_GUINAMESPACE_H
#define AC_GUINAMESPACE_H

#include <ac_corenamespace.h>

namespace I {

enum AcGuiInterfaces {
    IChildEntity = AcCoreInterfaceCount,
    IEntity,
    IParentEntity,
    ISubEntity,
    IPointsItem,
    IGripItem,
    IPlayCursor,
    AcGuiInterfaceCount
};

} // namespace I

namespace Ac {

enum SubEntityCurveFlags {
    NonCurveSubEntity = 0x0,
    CurveSubEntity = 0x1
};

enum SceneType {
    PitchScene,
    ControlScene,
    TimeLabelScene,
    PitchLabelScene,
    ControlLabelScene,
    SceneTypeCount
};

} // namespace Ac

#endif // AC_GUINAMESPACE_H
