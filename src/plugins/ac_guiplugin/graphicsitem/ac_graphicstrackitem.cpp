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
#include <ac_guiutil.h>
#include <ac_graphicsnoteitem.h>
#include <ac_note.h>
#include <ac_notelist.h>
#include <ac_track.h>
#include <QGraphicsItemGroup>

class AcGraphicsTrackItemPrivate : public AcGraphicsItemPrivate
{
public:
    AcGraphicsTrackItem *q;
    QGraphicsItemGroup *pitchItem;
    QGraphicsItemGroup *volumeItem;
    QList<AcGraphicsNoteItem*> noteItems;

    AcGraphicsTrackItemPrivate(AcGraphicsTrackItem *q, AcTrack *track)
        :   q(q)
        ,   pitchItem(new QGraphicsItemGroup)
        ,   volumeItem(new QGraphicsItemGroup)
    {
        dataObject = track;
        pitchItem->setZValue(1.0f);
        volumeItem->setZValue(1.0f);
    }

    virtual ~AcGraphicsTrackItemPrivate()
    {
        qDeleteAll(noteItems);
        delete volumeItem;
        delete pitchItem;
    }

    AcTrack *track() const
    {
        return dataObject->cast<AcTrack>();
    }

    void updateNoteItems()
    {
        updateItemsHelper(track()->notes()->children(), noteItems, q);
    }
};

AcGraphicsTrackItem::AcGraphicsTrackItem(AcTrack *track, QObject *parent)
    :   AcGraphicsItem(*(new AcGraphicsTrackItemPrivate(this, track)), parent)
{
    Q_D(AcGraphicsTrackItem);
    d->updateNoteItems();
}

QGraphicsItem *AcGraphicsTrackItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsTrackItem);
    switch (sceneType) {
    case PitchScene:
        return d->pitchItem;
    case VolumeScene:
        return d->volumeItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsTrackItem::updateDataObject(int i)
{
    if (AcTrack::NotesIndex == i) {
        Q_D(AcGraphicsTrackItem);
        d->updateNoteItems();
    }
}
