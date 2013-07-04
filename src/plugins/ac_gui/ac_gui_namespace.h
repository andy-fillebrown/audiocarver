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

#ifndef AC_GUI_NAMESPACE_H
#define AC_GUI_NAMESPACE_H

#include <ac_core_namespace.h>
#include <mi_gui_namespace.h>

namespace Ac {

enum GuiItemType {
    VelocityItem = Ac::CoreItemTypeCount,
    GripItem,
    PlayCursorItem,
    GuiItemTypeCount
};

enum GuiItemDataRole {
    HighlightRole = Ac::CoreItemDataRoleCount,
    OriginalPositionRole,
    PositionRole,
    CurveTypeRole
};

enum SceneType {
    UnspecifiedScene = -1,
    ControlLabelScene = 0,
    ControlScene,
    PitchLabelScene,
    PitchScene,
    TimeLabelScene,
    SceneTypeCount
};

enum TransformType {
    UnspecifiedTransform = -1,
    MainTransform = 0,
    UnitXTransform,
    UnitYTransform,
    TransformTypeCount
};

enum HighlightType {
    NoHighlight = 0,
    HoverHighlight,
    FullHighlight
};

enum DragType {
    Dragging,
    NotDragging
};

enum UndoCommands {
    UndoViewSettingsCommand = Mi::UndoCommandCount
};

}

#endif
