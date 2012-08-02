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

#ifndef AC_CORE_NAMESPACE_H
#define AC_CORE_NAMESPACE_H

#include "ac_core_global.h"
#include <mi_core_namespace.h>

namespace Ac {

enum ItemType {
    ScoreObjectItem = Mi::CoreItemTypeCount,
    ScoreItem,
    TrackItem,
    TrackListItem,
    NoteItem,
    NoteListItem,
    CurveItem,
    PitchCurveItem,
    ControlCurveItem,
    ControlCurveListItem,
    GridSettingsItem,
    GridLineItem,
    TimeGridLineItem,
    TimeGridLineListItem,
    PitchGridLineItem,
    PitchGridLineListItem,
    ControlGridLineItem,
    ControlGridLineListItem,
    ViewSettingsItem,
    ProjectSettingsItem,
    CoreItemTypeCount
};

enum ItemDataRole {
    PointsRole = Mi::ItemDataRoleCount,
    ControlTypeRole,
    LocationRole,
    LabelRole,
    PriorityRole,
    InstrumentRole,
    LengthRole,
    VolumeRole,
    StartTimeRole,
    ColorRole,
    VisibilityRole,
    RecordingRole,
    TimePositionRole,
    PitchPositionRole,
    ControlPositionRole,
    TimeScaleRole,
    PitchScaleRole,
    ControlScaleRole,
    OutputDirectoryRole,
    InstrumentDirectoryRole,
    AudioFileTypeRole,
    SampleRateRole,
    ControlRateRole,
    CurveRateRole,
    PlaybackTimeRole,
    SnapEnabledRole,
    GridSnapEnabledRole,
    TimeSnapRole,
    PitchSnapRole,
    ControlSnapRole
};

enum CurveType {
    NoCurve,
    BezierCurve
};

enum FilerType {
    CopyFiler,
    FileFiler
};

enum Color {
    red = 0xff000,
    lightGray = 0xc0c0c0
};

}

#endif
