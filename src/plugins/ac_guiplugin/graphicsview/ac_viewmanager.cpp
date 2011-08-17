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

#include "ac_viewmanager.h"
//#include <ac_guifactory.h>
#include <ac_pitchlabelview.h>
#include <ac_pitchview.h>
#include <ac_scenemanager.h>
//#include <ac_score.h>
#include <ac_timelabelview.h>
//#include <ac_viewsettings.h>
#include <ac_volumelabelview.h>
#include <ac_volumeview.h>
#include <QGraphicsView>
#include <QWidget>

class AcViewManagerPrivate
{
public:
    AcViewManager *q;
    AcSceneManager *sceneManager;
    AcPitchView *pitchView;
    AcVolumeView *volumeView;
    AcTimeLabelView *timeLabelView;
    AcPitchLabelView *pitchLabelView;
    AcVolumeLabelView *volumeLabelView;

    AcViewManagerPrivate(AcViewManager *q, QWidget *widget)
        :   q(q)
//        ,   sceneManager(AcGuiFactory::instance()->createSceneManager(q))
        ,   sceneManager(new AcSceneManager(q))
//        ,   pitchView(new AcPitchView(sceneManager->scene(Pitch), widget))
//        ,   volumeView(new AcVolumeView(sceneManager->scene(Volume), widget))
//        ,   timeLabelView(new AcTimeLabelView(sceneManager->scene(TimeLabel), widget))
//        ,   pitchLabelView(new AcPitchLabelView(sceneManager->scene(PitchLabel), widget))
//        ,   volumeLabelView(new AcVolumeLabelView(sceneManager->scene(VolumeLabel), widget))
    {}

    void updateViewCenters()
    {
        pitchView->updateCenter();
        volumeView->updateCenter();
//        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
//        timeLabelView->centerOn(pitchView->center().x() * viewSettings->timeScale(), sceneManager->scene(TimeLabelScene)->height() / 2.0f);
//        pitchView->centerOn(sceneManager->scene(PitchLabelScene)->width() / 2.0f, pitchView->center().y() * viewSettings->pitchScale());
//        volumeLabelView->centerOn(sceneManager->scene(VolumeLabelScene)->width() / 2.0f, volumeView->center().y() * viewSettings->volumeScale());
    }
};

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerPrivate(this, widget))
{
//    Q_CONNECT(AcScore::instance()->viewSettings(), SIGNAL(changed(int,QVariant)), this, SLOT(updateViewSettings(int,QVariant)));
}

AcViewManager::~AcViewManager()
{
    delete d;
}

//QGraphicsView *AcViewManager::pitchView() const
//{
//    return d->pitchView;
//}

//QGraphicsView *AcViewManager::volumeView() const
//{
//    return d->volumeView;
//}

//QGraphicsView *AcViewManager::timeLabelView() const
//{
//    return d->timeLabelView;
//}

//QGraphicsView *AcViewManager::pitchLabelView() const
//{
//    return d->pitchLabelView;
//}

//QGraphicsView *AcViewManager::volumeLabelView() const
//{
//    return d->volumeLabelView;
//}

//qreal AcViewManager::timePosition() const
//{
//    return d->pitchView->center().x();
//}

//void AcViewManager::setTimePosition(qreal position)
//{
//    d->pitchView->setCenter(position, pitchPosition());
//    d->volumeView->setCenter(position, volumePosition());
//}

//qreal AcViewManager::pitchPosition() const
//{
//    return d->pitchView->center().y();
//}

//void AcViewManager::setPitchPosition(qreal position)
//{
//    d->pitchView->setCenter(timePosition(), position);
//}

//qreal AcViewManager::volumePosition() const
//{
//    return d->volumeView->center().y();
//}

//void AcViewManager::setVolumePosition(qreal position)
//{
//    d->volumeView->setCenter(timePosition(), position);
//}

//qreal AcViewManager::timeScale() const
//{
//    return AcScore::instance()->viewSettings()->timeScale();
//    return 1.0f;
//}

//void AcViewManager::setTimeScale(qreal scale)
//{
//    AcScore::instance()->viewSettings()->setTimeScale(scale);
//}

//qreal AcViewManager::pitchScale() const
//{
//    return AcScore::instance()->viewSettings()->pitchScale();
//    return 1.0f;
//}

//void AcViewManager::setPitchScale(qreal scale)
//{
//    AcScore::instance()->viewSettings()->setPitchScale(scale);
//}

//qreal AcViewManager::volumeScale() const
//{
//    return AcScore::instance()->viewSettings()->volumeScale();
//    return 1.0f;
//}

//void AcViewManager::setVolumeScale(qreal scale)
//{
//    AcScore::instance()->viewSettings()->setVolumeScale(scale);
//}

//void AcViewManager::updateViews()
//{
//    d->pitchView->updateTransform();
//    d->volumeView->updateTransform();
//    d->updateViewCenters();
//}

//void AcViewManager::updateViewSettings(int i, const QVariant &value)
//{
//    switch (i) {
//    case ViewSettings::TimePosition:
//    case ViewSettings::PitchPosition:
//    case ViewSettings::VolumePosition:
//        d->updateViewCenters();
//        break;
//    case ViewSettings::TimeScale:
//    case ViewSettings::PitchScale:
//    case ViewSettings::VolumeScale:
//        updateViews();
//        break;
//    default:
//        break;
//    }
//}
