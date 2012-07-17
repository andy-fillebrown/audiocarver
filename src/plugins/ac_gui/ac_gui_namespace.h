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

#ifndef AC_GUI_NAMESPACE_H
#define AC_GUI_NAMESPACE_H

#include <ac_core_namespace.h>

#include <mi_gui_namespace.h>

namespace I {

enum AcGuiInterfaces {
    IChildEntity = MiGuiInterfaceCount,
    IEntity,
    IParentEntity,
    ISubEntity,
    IPointsItem,
    IGripItem,
    IPlayCursor,
    IGraphicsScene,
    IGraphicsView,
    IGraphicsViewGroup,
    IGraphicsViewManager,
    AcGuiInterfaceCount
};

} // namespace I

namespace Ac {

enum GuiItemType {
    GraphicsSceneItem = CoreItemTypeCount,
    GraphicsViewItem,
    GraphicsViewGroupItem,
    GuiItemTypeCount
};

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

enum GraphicsItemTransformType {
    MainTransform,
    UnitXTransform,
    UnitYTransform,
    GraphicsItemTransformTypeCount
};

} // namespace Ac

#endif // AC_GUI_NAMESPACE_H
