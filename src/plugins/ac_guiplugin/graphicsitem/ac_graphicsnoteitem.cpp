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
#include <ac_curvepoint.h>
#include <ac_graphicspitchpointitem.h>
#include <ac_graphicsvolumepointitem.h>
#include <ac_note.h>
#include <ac_pitchcurve.h>
#include <ac_scene_util.h>
#include <ac_volumecurve.h>
#include <mi_graphicspathitem.h>
#include <QBrush>
#include <QColor>
#include <QPen>

class AcGraphicsNoteItemPrivate : public AcGraphicsItemPrivate
{
public:
    AcGraphicsNoteItem *q;
    MiGraphicsPathItem *pitchLineItem;
    MiGraphicsPathItem *volumeLineItem;
    QList<AcGraphicsPitchPointItem*> pitchPointItems;
    QList<AcGraphicsVolumePointItem*> volumePointItems;

    AcGraphicsNoteItemPrivate(AcGraphicsNoteItem *q, AcNote *note)
        :   q(q)
        ,   pitchLineItem(new MiGraphicsPathItem)
        ,   volumeLineItem(new MiGraphicsPathItem)
    {
        dataObject = note;
        pitchLineItem->setData(0, quintptr(q));
        volumeLineItem->setData(0, quintptr(q));
        QPen pen(Qt::red);
        pen.setCosmetic(true);
        pen.setWidth(2);
        pitchLineItem->setPen(pen);
        volumeLineItem->setPen(pen);
        pitchLineItem->setBoundingRegionGranularity(1.0f);
        volumeLineItem->setBoundingRegionGranularity(1.0f);
    }

    virtual ~AcGraphicsNoteItemPrivate()
    {
        qDeleteAll(volumePointItems);
        qDeleteAll(pitchPointItems);
        delete volumeLineItem;
        delete pitchLineItem;
    }

    const AcNote *note() const
    {
        return dataObject->cast<AcNote>();
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
        updatePitchLineItem();
        updateVolumeLineItem();
    }

    void updatePitchLineItem()
    {
        QPainterPath path;
        const QList<AcCurvePoint*> &pts = pitchCurve()->children();
        if (pts.count() == 0) {
            pitchLineItem->setPath(path);
            return;
        }
        path.moveTo(pts[0]->x(), 127.0f - pts[0]->y());
        for (int i = 1;  i < pts.count();  ++i)
            path.lineTo(pts[i]->x(), 127.0f - pts[i]->y());
        pitchLineItem->setPath(path);
    }

    void updateVolumeLineItem()
    {
    }

    void updatePitchPointItems()
    {
        updateItemsHelper(pitchCurve()->children(), pitchPointItems, q);
    }

    void updateVolumePointItems()
    {
        updateItemsHelper(volumeCurve()->children(), volumePointItems, q);
    }

    void showPointItems()
    {
        updatePitchPointItems();
        updateVolumePointItems();
    }

    void hidePointItems()
    {
        qDeleteAll(volumePointItems);
        volumePointItems.clear();
        qDeleteAll(pitchPointItems);
        pitchPointItems.clear();
    }
};

AcGraphicsNoteItem::AcGraphicsNoteItem(AcNote *note, QObject *parent)
    :   AcGraphicsItem(*(new AcGraphicsNoteItemPrivate(this, note)), parent)
{
    Q_D(AcGraphicsNoteItem);
    d->update();
    Q_CONNECT(d->pitchCurve(), SIGNAL(changed(int)), this, SLOT(updatePitchCurve()));
    Q_CONNECT(d->volumeCurve(), SIGNAL(changed(int)), this, SLOT(updateVolumeCurve()));
}

QGraphicsItem *AcGraphicsNoteItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsNoteItem);
    switch (sceneType) {
    case PitchScene:
        return d->pitchLineItem;
    case VolumeScene:
        return d->volumeLineItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsNoteItem::highlight()
{
    Q_D(AcGraphicsNoteItem);
    d->showPointItems();
}

void AcGraphicsNoteItem::unhighlight()
{
    Q_D(AcGraphicsNoteItem);
    d->hidePointItems();
}

void AcGraphicsNoteItem::updatePitchCurve()
{
//    Q_D(AcGraphicsNoteItem);
//    d->updatePitchPointItems();
}

void AcGraphicsNoteItem::updateVolumeCurve()
{
//    Q_D(AcGraphicsNoteItem);
//    d->updateVolumePointItems();
}

void AcGraphicsNoteItem::updateDataObject(int i)
{
    Q_D(AcGraphicsNoteItem);
    switch (i) {
    case AcNote::PitchCurveIndex:
        d->updatePitchLineItem();
        break;
    case AcNote::VolumeCurveIndex:
        d->updateVolumeLineItem();
    }
}
