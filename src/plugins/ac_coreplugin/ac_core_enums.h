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

#ifndef AC_CORE_ENUMS_H
#define AC_CORE_ENUMS_H

#include <qnamespace.h>

enum ItemDataRole {
    ItemTypeRole = Qt::UserRole,
    ListTypeRole,
    PointsRole,
    LocationRole,
    LabelRole,
    PriorityRole,
    InstrumentRole,
    LengthRole,
    HeightRole,
    VolumeRole,
    ColorRole,
    VisibilityRole
};

enum ItemType {
    ListItem,
    ScoreItem,
    TrackItem,
    NoteItem,
    GridSettingsItem,
    TimeLineItem,
    PitchLineItem,
    ControlLineItem
};

enum CurveType {
    NoCurve,
    BezierCurve
};

#endif // AC_CORE_ENUMS_H
