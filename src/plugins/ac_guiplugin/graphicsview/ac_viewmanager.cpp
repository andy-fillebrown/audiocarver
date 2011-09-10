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
#include <ac_scene.h>
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
    SceneManager *sceneManager;
    AcPitchView *pitchView;
    AcVolumeView *controlView;
    AcTimeLabelView *timeLabelView;
    AcPitchLabelView *pitchLabelView;
    AcVolumeLabelView *controlLabelView;

    AcViewManagerPrivate(AcViewManager *q, QWidget *widget)
        :   q(q)
//        ,   sceneManager(AcGuiFactory::instance()->createSceneManager(q))
        ,   sceneManager(new SceneManager(q))
        ,   pitchView(new AcPitchView(sceneManager->pitchScene, widget))
        ,   controlView(new AcVolumeView(sceneManager->controlScene, widget))
        ,   timeLabelView(new AcTimeLabelView(sceneManager->timeLabelScene, widget))
        ,   pitchLabelView(new AcPitchLabelView(sceneManager->pitchLabelScene, widget))
        ,   controlLabelView(new AcVolumeLabelView(sceneManager->controlLabelScene, widget))
    {}

    void updateViewCenters()
    {
        pitchView->updateCenter();
        controlView->updateCenter();
        timeLabelView->centerOn(pitchView->center().x(), sceneManager->timeLabelScene->height() / 2.0f);
        pitchLabelView->centerOn(sceneManager->pitchLabelScene->width() / 2.0f, pitchView->center().y());
        controlLabelView->centerOn(sceneManager->controlLabelScene->width() / 2.0f, controlView->center().y());
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

QGraphicsView *AcViewManager::pitchView() const
{
    return d->pitchView;
}

QGraphicsView *AcViewManager::controlView() const
{
    return d->controlView;
}

QGraphicsView *AcViewManager::timeLabelView() const
{
    return d->timeLabelView;
}

QGraphicsView *AcViewManager::pitchLabelView() const
{
    return d->pitchLabelView;
}

QGraphicsView *AcViewManager::controlLabelView() const
{
    return d->controlLabelView;
}

void AcViewManager::setModel(AbstractItemModel *model)
{
    d->sceneManager->setModel(model);
}

void AcViewManager::viewAll()
{
//    QRectF rect;
//    QList<QGraphicsItem*> items = d->pitchView->items();
//    foreach(QGraphicsItem *item, items) {
//        QRectF itemRect = item->boundingRect();
//        rect |= itemRect;
//    }
//    d->pitchView->ensureVisible(rect);
}

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

void AcViewManager::updateViews()
{
    d->pitchView->updateTransform();
    d->controlView->updateTransform();
    d->updateViewCenters();
}

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
