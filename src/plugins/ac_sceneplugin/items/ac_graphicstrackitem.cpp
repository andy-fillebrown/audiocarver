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
#include <ac_controlscene.h>
#include <ac_scorescene.h>
#include <ac_track.h>
#include <QGraphicsItemGroup>

using namespace Private;

namespace Private {

AcGraphicsTrackItemData::AcGraphicsTrackItemData()
    :   track(0)
    ,   scoreGroup(new QGraphicsItemGroup)
    ,   controlGroup(new QGraphicsItemGroup)
{
    AcScoreScene::instance()->addItem(scoreGroup);
    AcControlScene::instance()->addItem(controlGroup);
}

AcGraphicsTrackItemData::~AcGraphicsTrackItemData()
{
    delete controlGroup;
    delete scoreGroup;
}


class AcGraphicsTrackItemPrivate : public AcGraphicsTrackItemData
{
public:
    AcGraphicsTrackItem *q;

    AcGraphicsTrackItemPrivate(AcGraphicsTrackItem *q)
        :   q(q)
    {}

    virtual ~AcGraphicsTrackItemPrivate()
    {}
};

} // namespace Private

AcGraphicsTrackItem::AcGraphicsTrackItem(AcTrack *track, QObject *parent)
    :   QObject(parent)
    ,   d_ptr(new AcGraphicsTrackItemPrivate(this))
{
    setDatabaseObject(track);
}

AcGraphicsTrackItem::~AcGraphicsTrackItem()
{
    delete d_ptr;
}

void AcGraphicsTrackItem::setDatabaseObject(AcTrack *track)
{
    Q_D(AcGraphicsTrackItem);
    if (d->track == track)
        return;
    if (d->track)
        d->track->disconnect(this);
    d->track = track;
    if (d->track)
        connect(d->track, SIGNAL(propertyChanged(QString)), SLOT(updateTrackProperty(QString)));
}

bool AcGraphicsTrackItem::isVisible() const
{
    Q_D(const AcGraphicsTrackItem);
    return d->scoreGroup->isVisible();
}

void AcGraphicsTrackItem::show()
{
    Q_D(AcGraphicsTrackItem);
    d->scoreGroup->show();
    d->controlGroup->show();
}

void AcGraphicsTrackItem::hide()
{
    Q_D(AcGraphicsTrackItem);
    d->scoreGroup->hide();
    d->controlGroup->hide();
}

void AcGraphicsTrackItem::updateTrackProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
