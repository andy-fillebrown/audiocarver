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
#include <ac_controlview.h>
#include <ac_pitchview.h>
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <ac_scoreview.h>
#include <ac_timeview.h>
#include <ac_valueview.h>
#include <ac_viewsettings.h>
#include <QGraphicsView>
#include <QWidget>

using namespace Private;

namespace Private {

class AcViewManagerData
{
public:
    AcViewManager *q;
    AcSceneManager *sceneManager;
    AcScoreView *scoreView;
    AcControlView *controlView;
    AcTimeView *timeView;
    AcPitchView *pitchView;
    AcValueView *valueView;

    AcViewManagerData(AcViewManager *q, QWidget *widget)
        :   q(q)
        ,   sceneManager(new AcSceneManager(q))
        ,   scoreView(new AcScoreView(sceneManager->scene(ScoreScene), widget))
        ,   controlView(new AcControlView(sceneManager->scene(ControlScene), widget))
        ,   timeView(new AcTimeView(sceneManager->scene(TimeScene), widget))
        ,   pitchView(new AcPitchView(sceneManager->scene(PitchScene), widget))
        ,   valueView(new AcValueView(sceneManager->scene(ValueScene), widget))
    {}

    void updateViewCenters()
    {
        scoreView->updateCenter();
        controlView->updateCenter();
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        timeView->centerOn(scoreView->center().x() * viewSettings->timeScale(), sceneManager->scene(TimeScene)->height() / 2.0f);
        pitchView->centerOn(sceneManager->scene(PitchScene)->width() / 2.0f, scoreView->center().y() * viewSettings->pitchScale());
        valueView->centerOn(sceneManager->scene(ValueScene)->width() / 2.0f, controlView->center().y() * viewSettings->valueScale());
    }
};

} // namespace Private

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerData(this, widget))
{
    connect(AcScore::instance()->viewSettings(), SIGNAL(propertyChanged(int)), SLOT(updateViewSettingsProperty(int)));
}

AcViewManager::~AcViewManager()
{
    delete d;
}

QGraphicsView *AcViewManager::scoreView() const
{
    return d->scoreView;
}

QGraphicsView *AcViewManager::controlView() const
{
    return d->controlView;
}

QGraphicsView *AcViewManager::timeView() const
{
    return d->timeView;
}

QGraphicsView *AcViewManager::pitchView() const
{
    return d->pitchView;
}

QGraphicsView *AcViewManager::valueView() const
{
    return d->valueView;
}

qreal AcViewManager::timePosition() const
{
    return d->scoreView->center().x();
}

void AcViewManager::setTimePosition(qreal position)
{
    d->scoreView->setCenter(position, pitchPosition());
    d->controlView->setCenter(position, valuePosition());
}

qreal AcViewManager::pitchPosition() const
{
    return d->scoreView->center().y();
}

void AcViewManager::setPitchPosition(qreal position)
{
    d->scoreView->setCenter(timePosition(), position);
}

qreal AcViewManager::valuePosition() const
{
    return d->controlView->center().y();
}

void AcViewManager::setValuePosition(qreal position)
{
    d->controlView->setCenter(timePosition(), position);
}

qreal AcViewManager::timeScale() const
{
    return AcScore::instance()->viewSettings()->timeScale();
}

void AcViewManager::setTimeScale(qreal scale)
{
    AcScore::instance()->viewSettings()->setTimeScale(scale);
}

qreal AcViewManager::pitchScale() const
{
    return AcScore::instance()->viewSettings()->pitchScale();
}

void AcViewManager::setPitchScale(qreal scale)
{
    AcScore::instance()->viewSettings()->setPitchScale(scale);
}

qreal AcViewManager::valueScale() const
{
    return AcScore::instance()->viewSettings()->valueScale();
}

void AcViewManager::setValueScale(qreal scale)
{
    AcScore::instance()->viewSettings()->setValueScale(scale);
}

void AcViewManager::updateViews()
{
    d->scoreView->updateTransform();
    d->controlView->updateTransform();
    d->updateViewCenters();
}

void AcViewManager::updateViewSettingsProperty(int propertyIndex)
{
    switch (propertyIndex) {
    case AcViewSettings::TimePosition:
    case AcViewSettings::PitchPosition:
    case AcViewSettings::ValuePosition:
        d->updateViewCenters();
        break;
    case AcViewSettings::TimeScale:
    case AcViewSettings::PitchScale:
    case AcViewSettings::ValueScale:
        updateViews();
        break;
    default:
        break;
    }
}
