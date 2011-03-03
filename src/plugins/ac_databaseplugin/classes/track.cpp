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

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class TrackPrivate
{
public:
    Database::List *notes;
    bool visible;
    qreal volume;

    TrackPrivate(Track *q)
        :   notes(new Database::List(q, q->propertyIndex("notes")))
        ,   visible(true)
        ,   volume(0.999999)
    {
        Q_CHECK_PTR(notes);
    }

    ~TrackPrivate()
    {
        delete notes;  notes = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

Track::Track(QObject *parent)
    :   Object(parent)
    ,   d(new TrackPrivate(this))
{
    Q_CHECK_PTR(d);
}

Track::~Track()
{
    delete d;  d = 0;
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

    emit propertyChanged(propertyIndex("visible"), this);
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

    emit propertyChanged(propertyIndex("volume"), this);
}

Database::List *Track::notes() const
{
    return d->notes;
}
