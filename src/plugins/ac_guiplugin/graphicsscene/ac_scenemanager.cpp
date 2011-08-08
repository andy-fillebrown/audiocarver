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
#include <ac_guiutil.h>
#include <ac_graphicspitchlineitem.h>
#include <ac_graphicstimelineitem.h>
#include <ac_graphicstrackitem.h>
#include <ac_graphicsvolumelineitem.h>
#include <ac_gridline.h>
#include <ac_gridlinelist.h>
#include <ac_pitchlabelscene.h>
#include <ac_pitchscene.h>
#include <ac_score.h>
#include <ac_timelabelscene.h>
#include <ac_track.h>
#include <ac_tracklist.h>
#include <ac_viewsettings.h>
#include <ac_volumelabelscene.h>
#include <ac_volumescene.h>
#include <mi_fontsettings.h>
#include <QFont>
#include <QFontMetrics>

template <typename T, typename ExpandRect>
static void updateItemVisibilitiesHelper(const QList<T*> &items, ExpandRect expandRect)
{
    int minPriority = INT_MAX;
    int prevPriority = 0;
    QRectF prevRect;
    foreach (T *item, items) {
        if (minPriority < item->priority())
            continue;
        QRectF curRect = item->labelRect();
        expandRect(curRect);
        if (prevRect.intersects(curRect))
            minPriority = qMax(prevPriority, item->priority());
        else {
            prevPriority = item->priority();
            prevRect = curRect;
        }
    }
    foreach (T *item, items) {
        if (item->priority() <= minPriority)
            item->show();
        else
            item->hide();
    }
}

static void expandTopLabelRect(QRectF &rect)
{
    rect.setWidth(3.0f * rect.width());
}

static void expandLeftLabelRect(QRectF &rect)
{
    rect.setTop(rect.top() - (1.5f * rect.height()));
}

class AcSceneManagerPrivate
{
public:
    AcSceneManager *q;
    AcPitchScene *pitchScene;
    AcVolumeScene *volumeScene;
    AcTimeLabelScene *timeLabelScene;
    AcPitchLabelScene *pitchLabelScene;
    AcVolumeLabelScene *volumeLabelScene;
    QList<AcGraphicsTrackItem*> trackItems;
    QList<AcGraphicsTimeLineItem*> timeLineItems;
    QList<AcGraphicsPitchLineItem*> pitchLineItems;
    QList<AcGraphicsVolumeLineItem*> volumeLineItems;
    QFontMetrics fontMetrics;

    AcSceneManagerPrivate(AcSceneManager *q)
        :   q(q)
        ,   pitchScene(new AcPitchScene(q))
        ,   volumeScene(new AcVolumeScene(q))
        ,   timeLabelScene(new AcTimeLabelScene(q))
        ,   pitchLabelScene(new AcPitchLabelScene(q))
        ,   volumeLabelScene(new AcVolumeLabelScene(q))
        ,   fontMetrics(font())
    {}

    virtual ~AcSceneManagerPrivate()
    {
        qDeleteAll(volumeLineItems);
        qDeleteAll(pitchLineItems);
        qDeleteAll(timeLineItems);
        qDeleteAll(trackItems);
    }

    QFont font() const
    {
        const MiFontSettings *fontSettings = AcScore::instance()->fontSettings();
        return QFont(fontSettings->family(), fontSettings->pointSize());
    }

    void init()
    {
        updateTrackItems();
        updateTimeLineItems();
        updatePitchLineItems();
        updateVolumeLineItems();
        updateFontMetrics();
        updateTimeLineItemVisibilities();
        updatePitchLineItemVisibilities();
        updateVolumeLineItemVisibilities();
    }

    void updateTrackItems()
    {
        updateItemsHelper(AcScore::instance()->tracks()->children(), trackItems, q);
    }

    void updateTimeLineItems()
    {
        updateItemsHelper(AcScore::instance()->timeLines()->children(), timeLineItems, q);
    }

    void updatePitchLineItems()
    {
        updateItemsHelper(AcScore::instance()->pitchLines()->children(), pitchLineItems, q);
    }

    void updateVolumeLineItems()
    {
        updateItemsHelper(AcScore::instance()->volumeLines()->children(), volumeLineItems, q);
    }

    void updateFontMetrics()
    {
        fontMetrics = QFontMetrics(font());
    }

    void updateTimeLineItemVisibilities()
    {
        updateItemVisibilitiesHelper(timeLineItems, expandTopLabelRect);
    }

    void updatePitchLineItemVisibilities()
    {
        updateItemVisibilitiesHelper(pitchLineItems, expandLeftLabelRect);
    }

    void updateVolumeLineItemVisibilities()
    {
        updateItemVisibilitiesHelper(volumeLineItems, expandLeftLabelRect);
    }
};

AcSceneManager *instance = 0;

AcSceneManager::AcSceneManager(QObject *parent)
    :   QObject(parent)
    ,   d(new AcSceneManagerPrivate(this))
{
    ::instance = this;
    d->init();
    AcScore *score = AcScore::instance();
    Q_CONNECT(score, SIGNAL(changed(int,QVariant)), this, SLOT(updateScore(int,QVariant)));
    Q_CONNECT(score->fontSettings(), SIGNAL(changed(int,QVariant)), this, SLOT(updateFontSettings(int,QVariant)));
    Q_CONNECT(score->viewSettings(), SIGNAL(changed(int,QVariant)), this, SLOT(updateViewSettings(int,QVariant)));
}

AcSceneManager::~AcSceneManager()
{
    delete d;
}

AcSceneManager *AcSceneManager::instance()
{
    return ::instance;
}

void AcSceneManager::updateScore(int i, const QVariant &value)
{
    switch (i) {
    case AcScore::TracksIndex:
        d->updateTrackItems();
        break;
    case AcScore::TimeLinesIndex:
        d->updateTimeLineItems();
        d->updateTimeLineItemVisibilities();
        break;
    case AcScore::PitchLinesIndex:
        d->updatePitchLineItems();
        d->updatePitchLineItemVisibilities();
        break;
    case AcScore::VolumeLinesIndex:
        d->updateVolumeLineItems();
        d->updateVolumeLineItemVisibilities();
        break;
    default:
        break;
    }
}

void AcSceneManager::updateFontSettings(int i, const QVariant &value)
{
    Q_UNUSED(i);
    d->updateFontMetrics();
    d->updateTimeLineItemVisibilities();
    d->updatePitchLineItemVisibilities();
    d->updateVolumeLineItemVisibilities();
}

void AcSceneManager::updateViewSettings(int i, const QVariant &value)
{
    switch (i) {
    case AcViewSettings::TimeScaleIndex:
        d->updateTimeLineItemVisibilities();
        break;
    case AcViewSettings::PitchScaleIndex:
        d->updatePitchLineItemVisibilities();
        break;
    case AcViewSettings::VolumeScaleIndex:
        d->updateVolumeLineItemVisibilities();
        break;
    default:
        break;
    }
}

QGraphicsScene *AcSceneManager::scene(SceneType sceneType) const
{
    switch (sceneType) {
    case PitchScene:
        return d->pitchScene;
    case VolumeScene:
        return d->volumeScene;
    case TimeLabelScene:
        return d->timeLabelScene;
    case PitchLabelScene:
        return d->pitchLabelScene;
    case VolumeLabelScene:
        return d->volumeLabelScene;
    default:
        break;
    }
    return 0;
}

void AcSceneManager::addItem(AcGraphicsItem *item)
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *sceneItem = item->sceneItem(SceneType(i));
        if (sceneItem)
            scene(SceneType(i))->addItem(sceneItem);
    }
}

const QFontMetrics &AcSceneManager::fontMetrics() const
{
    return d->fontMetrics;
}
