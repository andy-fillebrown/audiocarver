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

#include "ac_note.h"
#include <ac_pitchcurve.h>
#include <ac_volumecurve.h>

using namespace Private;

namespace Private {

class AcNoteData
{
public:
    AcPitchCurve *pitchCurve;
    AcVolumeCurve *volumeCurve;

    AcNoteData(AcNote *q)
        :   pitchCurve(new AcPitchCurve(q))
        ,   volumeCurve(new AcVolumeCurve(q))
    {}
};

} // namespace Private

AcNote::AcNote(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcNoteData(this))
{}

AcNote::~AcNote()
{
    delete d;
}

AcPitchCurve *AcNote::pitchCurve() const
{
    return d->pitchCurve;
}

AcVolumeCurve *AcNote::volumeCurve() const
{
    return d->volumeCurve;
}

MiObject *AcNote::findObject(const QString &className) const
{
    if ("PitchCurve" == className)
        return pitchCurve();
    if ("VolumeCurve" == className)
        return volumeCurve();
    return 0;
}

MiObject *AcNote::pitchCurveObject() const
{
    return pitchCurve();
}

MiObject *AcNote::volumeCurveObject() const
{
    return volumeCurve();
}
