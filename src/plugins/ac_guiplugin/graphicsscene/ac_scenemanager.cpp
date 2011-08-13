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

#include "ac_scenemanager.h"
#include <ac_pitchscene.h>
#include <ac_timelabelscene.h>
#include <ac_volumelabelscene.h>
#include <ac_volumescene.h>
//#include <ac_graphicspitchlineitem.h>
//#include <ac_graphicstimelineitem.h>
//#include <ac_graphicstrackitem.h>
//#include <ac_graphicsvolumelineitem.h>
#include <ac_pitchlabelscene.h>
//#include <ac_guiutil.h>
//#include <ac_propertyindexes.h>
//#include <mi_object.h>
#include <QFont>
#include <QFontMetrics>
#include <QVariant>

//template <typename T, typename ExpandRect>
//static void updateItemVisibilitiesHelper(const QList<T*> &items, ExpandRect expandRect)
//{
//    int minPriority = INT_MAX;
//    int prevPriority = 0;
//    QRectF prevRect;
//    foreach (T *item, items) {
//        if (minPriority < item->priority())
//            continue;
//        QRectF curRect = item->labelRect();
//        expandRect(curRect);
//        if (prevRect.intersects(curRect))
//            minPriority = qMax(prevPriority, item->priority());
//        else {
//            prevPriority = item->priority();
//            prevRect = curRect;
//        }
//    }
//    foreach (T *item, items) {
//        if (item->priority() <= minPriority)
//            item->show();
//        else
//            item->hide();
//    }
//}

//static void expandTopLabelRect(QRectF &rect)
//{
//    rect.setWidth(3.0f * rect.width());
//}

//static void expandLeftLabelRect(QRectF &rect)
//{
//    rect.setTop(rect.top() - (1.5f * rect.height()));
//}

class AcSceneManagerPrivate
{
public:
    AcSceneManager *q;
    AcPitchScene *pitchScene;
    AcVolumeScene *volumeScene;
    AcTimeLabelScene *timeLabelScene;
    AcPitchLabelScene *pitchLabelScene;
    AcVolumeLabelScene *volumeLabelScene;
//    QList<AcGraphicsTrackItem*> trackItems;
//    QList<AcGraphicsTimeLineItem*> timeLineItems;
//    QList<AcGraphicsPitchLineItem*> pitchLineItems;
//    QList<AcGraphicsVolumeLineItem*> volumeLineItems;
//    QFont font;
//    QFontMetrics fontMetrics;

    AcSceneManagerPrivate(AcSceneManager *q)
        :   q(q)
        ,   pitchScene(new AcPitchScene(q))
        ,   volumeScene(new AcVolumeScene(q))
        ,   timeLabelScene(new AcTimeLabelScene(q))
        ,   pitchLabelScene(new AcPitchLabelScene(q))
        ,   volumeLabelScene(new AcVolumeLabelScene(q))
//        ,   fontMetrics(font)
    {}

    virtual ~AcSceneManagerPrivate()
    {
//        qDeleteAll(volumeLineItems);
//        qDeleteAll(pitchLineItems);
//        qDeleteAll(timeLineItems);
//        qDeleteAll(trackItems);
    }

//    void updateTrackItems(const MiObjectList &tracks)
//    {
//        updateItemsHelper(tracks, trackItems, q);
//    }

//    void updateTimeLineItems(const MiObjectList &timeLines)
//    {
//        updateItemsHelper(timeLines, timeLineItems, q);
//    }

//    void updatePitchLineItems(const MiObjectList &pitchLines)
//    {
//        updateItemsHelper(pitchLines, pitchLineItems, q);
//    }

//    void updateVolumeLineItems(const MiObjectList &volumeLines)
//    {
//        updateItemsHelper(volumeLines, volumeLineItems, q);
//    }

//    void updateFontMetrics()
//    {
//        fontMetrics = QFontMetrics(font);
//    }

//    void updateTimeLineItemVisibilities()
//    {
//        updateItemVisibilitiesHelper(timeLineItems, expandTopLabelRect);
//    }

//    void updatePitchLineItemVisibilities()
//    {
//        updateItemVisibilitiesHelper(pitchLineItems, expandLeftLabelRect);
//    }

//    void updateVolumeLineItemVisibilities()
//    {
//        updateItemVisibilitiesHelper(volumeLineItems, expandLeftLabelRect);
//    }
};

AcSceneManager *instance = 0;
Score *score = 0;

AcSceneManager::AcSceneManager(QObject *parent)
    :   QObject(parent)
    ,   d(new AcSceneManagerPrivate(this))
{
    ::instance = this;

    Note *note = new Note;
    PointItems pts;
    pts.append(new PointItem(0.0f, 60.0f, PointItem::BezierCurve));
    pts.append(new PointItem(32.0f, 72.0f, PointItem::BezierCurve));
    pts.append(new PointItem(64.0f, 67.0f, PointItem::BezierCurve));
    pts.append(new PointItem(96.0f, 60.0f, PointItem::BezierCurve));
    pts.append(new PointItem(128.0f, 48.0f, PointItem::BezierCurve));
    foreach (PointItem *pt, pts)
        note->pitchCurve()->appendPoint(pt);
    note->pitchCurve()->update();

    Track *track = new Track;
    track->appendNote(note);

    score = new Score;
    score->appendTrack(track);
    addObject(score);
}

AcSceneManager::~AcSceneManager()
{
    delete score;
    delete d;
}

AcSceneManager *AcSceneManager::instance()
{
    return ::instance;
}

//void AcSceneManager::updateScore(int i, const QVariant &value)
//{
//    switch (i) {
//    case Score::Tracks:
//        d->updateTrackItems(value.value<MiObjectList>());
//        break;
//    case Score::TimeLines:
//        d->updateTimeLineItems(value.value<MiObjectList>());
//        d->updateTimeLineItemVisibilities();
//        break;
//    case Score::PitchLines:
//        d->updatePitchLineItems(value.value<MiObjectList>());
//        d->updatePitchLineItemVisibilities();
//        break;
//    case Score::VolumeLines:
//        d->updateVolumeLineItems(value.value<MiObjectList>());
//        d->updateVolumeLineItemVisibilities();
//        break;
//    default:
//        break;
//    }
//}

//void AcSceneManager::updateFontSettings(int i, const QVariant &value)
//{
//    switch (i) {
//    case FontSettings::Family:
//        d->font.setFamily(value.toString());
//        break;
//    case FontSettings::PointSize:
//        d->font.setPointSize(value.toInt());
//        break;
//    }

//    d->updateFontMetrics();
//    d->updateTimeLineItemVisibilities();
//    d->updatePitchLineItemVisibilities();
//    d->updateVolumeLineItemVisibilities();
//}

//void AcSceneManager::updateViewSettings(int i)
//{
//    switch (i) {
//    case ViewSettings::TimeScale:
//        d->updateTimeLineItemVisibilities();
//        break;
//    case ViewSettings::PitchScale:
//        d->updatePitchLineItemVisibilities();
//        break;
//    case ViewSettings::VolumeScale:
//        d->updateVolumeLineItemVisibilities();
//        break;
//    default:
//        break;
//    }
//}

QGraphicsScene *AcSceneManager::scene(SceneType sceneType) const
{
    switch (sceneType) {
    case Pitch:
        return d->pitchScene;
    case Volume:
        return d->volumeScene;
    case TimeLabel:
        return d->timeLabelScene;
    case PitchLabel:
        return d->pitchLabelScene;
    case VolumeLabel:
        return d->volumeLabelScene;
    default:
        break;
    }
    return 0;
}

//void AcSceneManager::addItem(AcGraphicsItem *item)
//{
//    for (int i = 0;  i < SceneTypeCount;  ++i) {
//        QGraphicsItem *sceneItem = item->sceneItem(SceneType(i));
//        if (sceneItem)
//            scene(SceneType(i))->addItem(sceneItem);
//    }
//}

void AcSceneManager::addObject(Object *object)
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = object->item(SceneType(i));
        if (item)
            scene(SceneType(i))->addItem(item);
    }
}

//const QFont &AcSceneManager::font() const
//{
//    return d->font;
//}

//const QFontMetrics &AcSceneManager::fontMetrics() const
//{
//    return d->fontMetrics;
//}
