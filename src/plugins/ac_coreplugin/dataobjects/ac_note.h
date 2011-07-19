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

#ifndef AC_NOTE_H
#define AC_NOTE_H

#include <mi_object.h>
#include <ac_controlcurve.h>
#include <ac_pitchcurve.h>

namespace Private {

class AcNoteData
{
public:
    AcPitchCurve *pitchCurve;
    AcControlCurveList *controlCurves;

    AcNoteData(QObject *q)
        :   pitchCurve(new AcPitchCurve(q))
        ,   controlCurves(new AcControlCurveList(q))
    {}

    virtual ~AcNoteData()
    {}
};

} // namespace Private

class AC_CORE_EXPORT AcNote : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AcNote)
    Q_PROPERTY(AcPitchCurve* pitchCurve READ pitchCurve)
    Q_PROPERTY(AcControlCurveList* controlCurves READ controlCurves)

public:
    enum Properties {
        PitchCurve = MiObject::PropertyCount,
        VolumeCurve,
        PropertyCount
    };

    AcNote(QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::AcNoteData(this))
    {}

    virtual ~AcNote()
    {
        delete d;
    }

    AcPitchCurve *pitchCurve() const
    {
        return d->pitchCurve;
    }

    AcControlCurveList *controlCurves() const
    {
        return d->controlCurves;
    }

private:
    Private::AcNoteData *d;
};

typedef MiList<AcNote> AcNoteList;

Q_DECLARE_METATYPE(AcNoteList*)

#endif // AC_NOTE_H
