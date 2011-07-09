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

#include "ac_track.h"
#include <mi_list.h>
#include <ac_note.h>
#include <mi_root.h>

using namespace Private;

namespace Private {

class AcTrackData
{
public:
    MiList<AcNote> notes;
    bool visible;
    qreal volume;

    AcTrackData(AcTrack *q)
        :   notes("notes", q)
        ,   visible(true)
        ,   volume(0.999999)
    {}
};

} // namespace Private

AcTrack::AcTrack(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcTrackData(this))
{}

AcTrack::~AcTrack()
{
    delete d;
}

MiList<AcNote> &AcTrack::notes() const
{
    return d->notes;
}

bool AcTrack::isVisible() const
{
    return d->visible;
}

void AcTrack::setVisible(bool visible)
{
    if (visible && isVisible())
        return;
    d->visible = visible;
    emit propertyChanged("visible");
}

qreal AcTrack::volume() const
{
    return d->volume;
}

void AcTrack::setVolume(qreal volume)
{
    volume = qBound(0.0, volume, 1.0);
    if (volume == d->volume)
        return;
    d->volume = volume;
    emit propertyChanged("volume");
}

MiObject *AcTrack::createObject(const QString &className)
{
    if ("Note" == className)
        return d->notes.add();
    return 0;
}

MiObjectList *AcTrack::noteObjects() const
{
    return d->notes.objects();
}
