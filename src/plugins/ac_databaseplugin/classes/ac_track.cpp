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

#include <ac_note.h>

#include <mi_list.h>

using namespace Private;

namespace Private {

class AcTrackData
{
public:
    MiList *notes;
    bool visible;
    qreal volume;

    AcTrackData(AcTrack *q)
        :   notes(new MiList(q, q->propertyIndex("notes")))
        ,   visible(true)
        ,   volume(0.999999)
    {}

    ~AcTrackData()
    {
        delete notes;
    }
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

MiList *AcTrack::notes() const
{
    return d->notes;
}

bool AcTrack::isVisible() const
{
    return d->visible;
}

void AcTrack::setVisibility(bool visible)
{
    if (visible && isVisible())
        return;
    d->visible = visible;
    emit propertyChanged(propertyIndex("visible"));
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
    emit propertyChanged(propertyIndex("volume"));
}

MiObject *AcTrack::createObject(const QString &className)
{
    if (className == "Note") {
        AcNote *note = new AcNote(this);
        d->notes->append(note);
        return note;
    }
    return 0;
}

MiObject *AcTrack::findObject(const QString &className) const
{
    Q_UNUSED(className);
    return 0;
}
