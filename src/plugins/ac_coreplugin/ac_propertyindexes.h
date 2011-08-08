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

#ifndef AC_PROPERTYINDEXES_H
#define AC_PROPERTYINDEXES_H

#include <mi_propertyindexes.h>

namespace Properties {

namespace ScoreObject {
enum Index {
    Volume = Object::Count,
    Color,
    PitchCurve,
    VolumeCurve,
    Count
};
}

namespace Score {
enum Index {
    Length = ScoreObject::Count,
    Tracks,
    TimeLines,
    PitchLines,
    VolumeLines,
    Settings,
    Count
};
}

namespace TrackList {
typedef ListObject::Index Index;
}

namespace Track {
enum Index {
    Notes = ScoreObject::Count,
    Count
};
}

namespace NoteList {
typedef SortedListObject::Index Index;
}

namespace Note {
typedef ScoreObject::Index Index;
}

namespace Curve {
typedef SortedListObject::Index Index;
}

namespace PitchCurve {
typedef Curve::Index Index;
}

namespace VolumeCurve {
typedef Curve::Index Index;
}

namespace Point {
enum Index {
    X = Object::Count,
    Y,
    Count
};
}

namespace CurvePoint {
enum Index {
    CurveType = Point::Count,
    StretchType,
    Count
};
}

namespace PitchPoint {
typedef CurvePoint::Index Index;
}

namespace VolumePoint {
typedef CurvePoint::Index Index;
}

namespace GridLineList {
typedef SortedListObject::Index Index;
}

namespace GridLine {
enum Index {
    Location = Object::Count,
    Label,
    Priority,
    Color,
    Count
};
}

namespace TimeLineList {
typedef GridLineList::Index Index;
}

namespace PitchLineList {
typedef GridLineList::Index Index;
}

namespace VolumeLineList {
typedef GridLineList::Index Index;
}

namespace GridSettings {
enum Index {
    Visible = Object::Count,
    Count
};
}

namespace ViewSettings {
enum Index {
    TimePosition = Object::Count,
    PitchPosition,
    VolumePosition,
    TimeScale,
    PitchScale,
    VolumeScale,
    Count
};
}

} // namespace Properties

#endif // AC_PROPERTYINDEXES_H
