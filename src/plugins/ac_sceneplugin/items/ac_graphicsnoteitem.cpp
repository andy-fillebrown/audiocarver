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

#include "ac_graphicsnoteitem.h"
#include <ac_graphicscontrolpointitem.h>
#include <ac_graphicsscorepointitem.h>
#include <ac_note.h>
#include <ac_pitchcurve.h>
#include <ac_point.h>
#include <ac_volumecurve.h>
#include <mi_list.h>
#include <QGraphicsPathItem>

using namespace Private;

namespace Private {

class AcGraphicsNoteItemPrivate : public AcGraphicsItemData
{
public:
    AcGraphicsNoteItem *q;
    QGraphicsPathItem *scoreItem;
    QGraphicsPathItem *controlItem;
    QList<AcGraphicsScorePointItem*> scorePointItems;
    QList<AcGraphicsControlPointItem*> controlPointItems;

    AcGraphicsNoteItemPrivate(AcGraphicsNoteItem *q, AcNote *note)
        :   q(q)
        ,   scoreItem(new QGraphicsPathItem)
        ,   controlItem(new QGraphicsPathItem)
    {
        databaseObject = note;
    }

    virtual ~AcGraphicsNoteItemPrivate()
    {
        qDeleteAll(controlPointItems);
        qDeleteAll(scorePointItems);
        delete controlItem;
        delete scoreItem;
    }

    const AcNote *note() const
    {
        return qobject_cast<AcNote*>(databaseObject);
    }

    const AcCurve *pitchCurve() const
    {
        return note()->pitchCurve();
    }

    const AcCurve *volumeCurve() const
    {
        return note()->volumeCurve();
    }

    void update()
    {
        updateScorePointItems();
        updateControlPointItems();
    }

    void updateScorePointItems()
    {
        updateItemsHelper(pitchCurve()->points().list(), scorePointItems, q);
        q->addItems(scorePointItems);
    }

    void updateControlPointItems()
    {
        updateItemsHelper(volumeCurve()->points().list(), controlPointItems, q);
        q->addItems(controlPointItems);
    }
};

} // namespace Private

AcGraphicsNoteItem::AcGraphicsNoteItem(AcNote *note, QObject *parent)
    :   AcGraphicsItem(*(new AcGraphicsNoteItemPrivate(this, note)), parent)
{
    Q_D(AcGraphicsNoteItem);
    d->update();
    updateDatabaseObjectProperty(AcNote::PitchCurve);
    updateDatabaseObjectProperty(AcNote::VolumeCurve);
}

AcGraphicsNoteItem::~AcGraphicsNoteItem()
{}

QGraphicsItem *AcGraphicsNoteItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsNoteItem);
    switch (sceneType) {
    case ScoreScene:
        return d->scoreItem;
    case ControlScene:
        return d->controlItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsNoteItem::updatePitchCurveProperty(int propertyIndex)
{
    if (AcCurve::Points == propertyIndex) {
        Q_D(AcGraphicsNoteItem);
        d->updateScorePointItems();
    }
}

void AcGraphicsNoteItem::updateVolumeCurveProperty(int propertyIndex)
{
    if (AcCurve::Points == propertyIndex) {
        Q_D(AcGraphicsNoteItem);
        d->updateControlPointItems();
    }
}

void AcGraphicsNoteItem::updateDatabaseObjectProperty(int propertyIndex)
{
    Q_D(AcGraphicsNoteItem);
    switch (propertyIndex) {
    case AcNote::PitchCurve:
        connect(d->pitchCurve(), SIGNAL(propertyChanged(int)), SLOT(updatePitchCurveProperty(int)), Qt::UniqueConnection);
        break;
    case AcNote::VolumeCurve:
        connect(d->volumeCurve(), SIGNAL(propertyChanged(int)), SLOT(updateVolumeCurveProperty(int)), Qt::UniqueConnection);
        break;
    default:
        break;
    }
}
