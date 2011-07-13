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
#include <ac_viewsettings.h>
#include <ac_volumecurve.h>
#include <mi_list.h>
#include <QBrush>
#include <QColor>
#include <QGraphicsPathItem>
#include <QPen>

using namespace Private;

namespace Private {

class AcGraphicsNoteItemPrivate : public AcScaledGraphicsItemData
{
public:
    AcGraphicsNoteItem *q;
    QGraphicsPathItem *scoreLineItem;
    QGraphicsPathItem *controlLineItem;
    QList<AcGraphicsScorePointItem*> scorePointItems;
    QList<AcGraphicsControlPointItem*> controlPointItems;

    AcGraphicsNoteItemPrivate(AcGraphicsNoteItem *q, AcNote *note)
        :   q(q)
        ,   scoreLineItem(new QGraphicsPathItem)
        ,   controlLineItem(new QGraphicsPathItem)
    {
        databaseObject = note;
        scoreLineItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        QPen pen(Qt::red);
        pen.setWidth(2);
        scoreLineItem->setPen(pen);
        controlLineItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }

    virtual ~AcGraphicsNoteItemPrivate()
    {
        qDeleteAll(controlPointItems);
        qDeleteAll(scorePointItems);
        delete controlLineItem;
        delete scoreLineItem;
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
        updateScoreLineItem();
        updateControlLineItem();
        updateScorePointItems();
        updateControlPointItems();
    }

    void updateScoreLineItem()
    {
        QPainterPath path;
        const QList<AcPoint*> &points = pitchCurve()->points().list();
        if (points.count() == 0) {
            scoreLineItem->setPath(path);
            return;
        }
        const qreal timeScale = viewSettings()->timeScale();
        const qreal pitchScale = viewSettings()->pitchScale();
        path.moveTo(timeScale * points[0]->x(), pitchScale * (127.0f - points[0]->y()));
        for (int i = 1;  i < points.count();  ++i)
            path.lineTo(timeScale * points[i]->x(), pitchScale * (127.0f - points[i]->y()));
        scoreLineItem->setPath(path);
    }

    void updateControlLineItem()
    {
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
    :   AcScaledGraphicsItem(*(new AcGraphicsNoteItemPrivate(this, note)), parent)
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
        return d->scoreLineItem;
    case ControlScene:
        return d->controlLineItem;
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

void AcGraphicsNoteItem::updateViewSettingsProperty(int propertyIndex)
{
    Q_D(AcGraphicsNoteItem);
    switch (propertyIndex) {
    case AcViewSettings::TimeScale:
        d->updateScoreLineItem();
        d->updateControlLineItem();
        break;
    case AcViewSettings::PitchScale:
        d->updateScoreLineItem();
        break;
    case AcViewSettings::ValueScale:
        d->updateControlLineItem();
        break;
    default:
        break;
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
