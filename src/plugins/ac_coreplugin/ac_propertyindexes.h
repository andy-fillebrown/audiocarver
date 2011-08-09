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

struct ScoreObject : public Object {
    enum Index {
        Volume = Object::Count,
        Color,
        PitchCurve,
        VolumeCurve,
        Count
    };
};

struct Score : public ScoreObject {
    enum Index {
        Length = ScoreObject::Count,
        Tracks,
        TimeLines,
        PitchLines,
        VolumeLines,
        Settings,
        Count
    };
};

struct TrackList : public ListObject {
    typedef ListObject::Index Index;
};

struct Track : public ScoreObject {
    enum Index {
        Notes = ScoreObject::Count,
        Count
    };
};

struct NoteList : public SortedListObject {
    typedef SortedListObject::Index Index;
};

struct Note : public ScoreObject {
    typedef ScoreObject::Index Index;
};

struct Curve : public SortedListObject {
    typedef SortedListObject::Index Index;
};

struct PitchCurve : public Curve {
    typedef Curve::Index Index;
};

struct VolumeCurve : public Curve {
    typedef Curve::Index Index;
};

struct Point: public Object {
    enum Index {
        X = Object::Count,
        Y,
        Count
    };
};

struct CurvePoint : public Point {
    enum Index {
        CurveType = Point::Count,
        StretchType,
        Count
    };
};

struct PitchPoint : public CurvePoint {
    typedef CurvePoint::Index Index;
};

struct VolumePoint : public CurvePoint {
    typedef CurvePoint::Index Index;
};

struct GridLineList : public SortedListObject {
    typedef SortedListObject::Index Index;
};

struct GridLine : public Object {
    enum Index {
        Location = Object::Count,
        Label,
        Priority,
        Color,
        Count
    };
};

struct TimeLineList : public GridLineList {
    typedef GridLineList::Index Index;
};

struct PitchLineList : public GridLineList {
    typedef GridLineList::Index Index;
};

struct VolumeLineList : public GridLineList {
    typedef GridLineList::Index Index;
};

struct GridSettings : public Object {
    enum Index {
        Visible = Object::Count,
        Count
    };
};

struct ViewSettings : public Object {
    enum Index {
        TimePosition = Object::Count,
        PitchPosition,
        VolumePosition,
        TimeScale,
        PitchScale,
        VolumeScale,
        Count
    };
};

#endif // AC_PROPERTYINDEXES_H
