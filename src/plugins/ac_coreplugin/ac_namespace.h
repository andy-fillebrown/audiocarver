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

#ifndef AC_NAMESPACE_H
#define AC_NAMESPACE_H

#include <ac_global.h>

#include <mi_namespace.h>

namespace Ac {

enum ItemType {
    ScoreItem = Mi::ItemTypeCount,
    TrackItem,
    NoteItem,
    PitchCurveItem,
    ControlCurveItem,
    GridSettingsItem,
    TimeGridLineItem,
    PitchGridLineItem,
    ControlGridLineItem,
    ViewSettingsItem,
    ProjectSettingsItem
};

enum ItemDataRole {
    PointsRole = Mi::ItemDataRoleCount,
    ControlIdRole,
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

enum InterfaceType {
    EntityInterface = Mi::InterfaceTypeCount,
    ParentEntityInterface,
    SubEntityInterface,
    PointsInterface,
    PointsItemInterface,
    GripItemInterface,
    ReaderInterface,
    WriterInterface,
    FileFilerInterface,
    CopyFilerInterface,
    PlayCursorInterface
};

enum CurveType {
    NoCurve,
    BezierCurve
};

enum FilerType {
    XmlCopyFiler,
    XmlFileFiler
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

#endif // AC_NAMESPACE_H
