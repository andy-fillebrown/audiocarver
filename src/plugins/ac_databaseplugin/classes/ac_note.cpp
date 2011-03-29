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

#include <ac_fcurve.h>

using namespace Private;

namespace Private {

class AcNoteData
{
public:
    int pointCount;
    AcFCurve *pitchCurve;

    AcNoteData()
        :   pointCount(64)
        ,   pitchCurve(0)
    {}
};

} // namespace Private

AcNote::AcNote(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcNoteData)
{}

AcNote::~AcNote()
{
    delete d;
}

int AcNote::pointCount() const
{
    return d->pointCount;
}

void AcNote::setPointCount(int count)
{
    if (pointCount() == count)
        return;
    d->pointCount = count;
    emit propertyChanged(propertyIndex("pointCount"));
}

MiObject *AcNote::pitchCurve() const
{
    return d->pitchCurve;
}

void AcNote::setPitchCurve(MiObject *curve)
{
    if (pitchCurve() == curve)
        return;
    d->pitchCurve = qobject_cast<AcFCurve*>(curve);
    emit propertyChanged(propertyIndex("pitchCurve"));
}
