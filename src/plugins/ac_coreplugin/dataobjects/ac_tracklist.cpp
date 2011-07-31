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

#include "ac_tracklist.h"
#include <ac_track.h>

AcTrackList::AcTrackList(int propertyIndex)
    :   MiListObject(*(new AcTrackListPrivate(this, propertyIndex)))
{
    Q_D(AcTrackList);
    d->addChild(new AcTrack);
}

const QList<AcTrack*> &AcTrackList::children() const
{
    return reinterpret_cast<const QList<AcTrack*>&>(QObject::children());
}

void AcTrackList::addChild(MiObject *child)
{
    if (!qobject_cast<AcTrack*>(child))
        return;
    MiListObject::addChild(child);
}
