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
#include <ac_graphicsnoteitem.h>
#include <ac_note.h>
#include <ac_scorescene.h>
#include <ac_track.h>
#include <mi_list.h>
#include <QGraphicsItemGroup>

using namespace Private;

namespace Private {

class AcGraphicsTrackItemPrivate : public AcGraphicsItemData
{
public:
    AcGraphicsTrackItem *q;
    QGraphicsItemGroup *scoreGroup;
    QGraphicsItemGroup *controlGroup;
    QList<AcGraphicsNoteItem*> noteItems;

    AcGraphicsTrackItemPrivate(AcGraphicsTrackItem *q, AcTrack *track)
        :   q(q)
        ,   scoreGroup(new QGraphicsItemGroup)
        ,   controlGroup(new QGraphicsItemGroup)
    {
        databaseObject = track;
    }

    virtual ~AcGraphicsTrackItemPrivate()
    {
        qDeleteAll(noteItems);
        delete controlGroup;
        delete scoreGroup;
    }

    AcTrack *track() const
    {
        return qobject_cast<AcTrack*>(databaseObject);
    }

    void updateNoteItems()
    {
        updateItemsHelper(track()->notes().list(), noteItems, q);
        q->addItems(noteItems);
    }
};

} // namespace Private

AcGraphicsTrackItem::AcGraphicsTrackItem(AcTrack *track, QObject *parent)
    :   AcGraphicsItem(*(new AcGraphicsTrackItemPrivate(this, track)), parent)
{
    Q_D(AcGraphicsTrackItem);
    d->updateNoteItems();
}

AcGraphicsTrackItem::~AcGraphicsTrackItem()
{}

QGraphicsItem *AcGraphicsTrackItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsTrackItem);
    switch (sceneType) {
    case ScoreScene:
        return d->scoreGroup;
    case ControlScene:
        return d->controlGroup;
    default:
        break;
    }
    return 0;
}

void AcGraphicsTrackItem::updateDatabaseObjectProperty(const QString &propertyName)
{
    if ("notes" == propertyName) {
        Q_D(AcGraphicsTrackItem);
        d->updateNoteItems();
    }
}
