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

#include "ac_graphicstrackitem.h"
#include <ac_track.h>
#include <QGraphicsItemGroup>

using namespace Private;

namespace Private {

class AcGraphicsTrackItemData
{
public:
    AcGraphicsTrackItem *q;
    AcTrack *track;
    QGraphicsItemGroup *scoreGroup;
    QGraphicsItemGroup *controlGroup;

    AcGraphicsTrackItemData(AcGraphicsTrackItem *q)
        :   q(q)
        ,   track(0)
    {}
};

} // namespace Private

AcGraphicsTrackItem::AcGraphicsTrackItem(AcTrack *track, QObject *parent)
    :   QObject(parent)
    ,   d(new AcGraphicsTrackItemData(this))
{
    setDatabaseObject(track);
}

AcGraphicsTrackItem::~AcGraphicsTrackItem()
{
    delete d;
}

void AcGraphicsTrackItem::setDatabaseObject(AcTrack *track)
{
    if (d->track == track)
        return;
    d->track = track;
}

bool AcGraphicsTrackItem::isVisible() const
{
    return d->scoreGroup->isVisible();
}

void AcGraphicsTrackItem::show()
{
    d->scoreGroup->show();
    d->controlGroup->show();
}

void AcGraphicsTrackItem::hide()
{
    d->scoreGroup->hide();
    d->controlGroup->hide();
}

void AcGraphicsTrackItem::updateTrackProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
