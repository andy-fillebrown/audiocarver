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

#include "track.h"

#include "note.h"

#include <databaseplugin/classes/list.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class TrackData
{
public:
    Database::List *notes;
    bool visible;
    qreal volume;

    TrackData(Track *q)
        :   notes(new Database::List(q, q->propertyIndex("notes")))
        ,   visible(true)
        ,   volume(0.999999)
    {}

    ~TrackData()
    {
        delete notes;
    }
};

} // namespace Internal
} // namespace AudioCarver

Track::Track(QObject *parent)
    :   Object(parent)
    ,   d(new TrackData(this))
{}

Track::~Track()
{
    delete d;
}

bool Track::isVisible() const
{
    return d->visible;
}

void Track::setVisibility(bool visible)
{
    if (visible && isVisible())
        return;
    d->visible = visible;
    emit propertyChanged(propertyIndex("visible"));
}

qreal Track::volume() const
{
    return d->volume;
}

void Track::setVolume(qreal volume)
{
    volume = qBound(0.0, volume, 1.0);
    if (volume == d->volume)
        return;
    d->volume = volume;
    emit propertyChanged(propertyIndex("volume"));
}

Note *Track::createNote()
{
    Note *note = new Note(this);
    d->notes->append(note);
    return note;
}

Database::List *Track::notes() const
{
    return d->notes;
}
