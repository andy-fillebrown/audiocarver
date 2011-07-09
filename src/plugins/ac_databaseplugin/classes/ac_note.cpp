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
#include <ac_point.h>
#include <mi_list.h>
#include <mi_root.h>

using namespace Private;

namespace Private {

class AcNoteData
{
public:
    AcNote *q;
    MiList<AcPitchPoint> pitchPoints;
    MiList<AcVolumePoint> volumePoints;

    AcNoteData(AcNote *q)
        :   q(q)
        ,   pitchPoints("pitchPoints", q, q->root())
        ,   volumePoints("volumePoints", q, q->root())
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

MiList<AcPitchPoint> &AcNote::pitchPoints() const
{
    return d->pitchPoints;
}

MiList<AcVolumePoint> &AcNote::volumePoints() const
{
    return d->volumePoints;
}

MiObject *AcNote::createObject(const QString &className)
{
    if ("PitchPoint" == className)
        return d->pitchPoints.add();
    if ("VolumePoint" == className)
        return d->volumePoints.add();
    return 0;
}

MiObjectList *AcNote::pitchPointObjects() const
{
    return d->pitchPoints.objects();
}

MiObjectList *AcNote::volumePointObjects() const
{
    return d->volumePoints.objects();
}
