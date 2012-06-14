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

#ifndef AC_CORENAMESPACE_H
#define AC_CORENAMESPACE_H

#include <ac_coreglobal.h>

#include <mi_corenamespace.h>

namespace I {

enum AcCoreInterfaces {
    IPoints = MiCoreInterfaceCount,
    AcCoreInterfaceCount
};

} // namespace I

namespace Ac {

enum ItemType {
    ScoreObjectItem = Mi::ItemTypeCount,
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
    GridLine,
    TimeGridLineItem,
    TimeGridLineListItem,
    PitchGridLineItem,
    PitchGridLineListItem,
    ControlGridLineItem,
    ControlGridLineListItem,
    ViewSettingsItem,
    ProjectSettingsItem
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
    XmlCopyFiler,
    XmlFileFiler
};

enum Color {
    red = 0xff000,
    lightGray = 0xc0c0c0
};

} // namespace Ac

#endif // AC_NAMESPACE_H
