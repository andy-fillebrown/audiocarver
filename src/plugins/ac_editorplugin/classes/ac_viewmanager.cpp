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
#include <ac_controllerview.h>
#include <ac_pitchview.h>
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <ac_scoreview.h>
#include <ac_timeview.h>
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
    AcControllerView *controllerView;
    AcPitchView *pitchView;
    AcTimeView *timeView;

    AcViewManagerData(AcViewManager *q, QWidget *widget)
        :   q(q)
        ,   sceneManager(new AcSceneManager(q))
        ,   scoreView(new AcScoreView(sceneManager->scoreScene(), widget))
        ,   controllerView(new AcControllerView(sceneManager->controllerScene(), widget))
        ,   pitchView(new AcPitchView(sceneManager->pitchScene(), widget))
        ,   timeView(new AcTimeView(sceneManager->timeScene(), widget))
    {}

    void updateViewCenters()
    {
        scoreView->updateCenter();
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        pitchView->centerOn(sceneManager->pitchScene()->width() / 2.0f, scoreView->center().y() * viewSettings->scaleY());
        timeView->centerOn(scoreView->center().x() * viewSettings->scaleX(), sceneManager->timeScene()->height() / 2.0f);
    }
};

} // namespace Private

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerData(this, widget))
{
    connect(AcScore::instance()->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
}

AcViewManager::~AcViewManager()
{
    delete d;
}

QGraphicsView *AcViewManager::scoreView() const
{
    return d->scoreView;
}

QGraphicsView *AcViewManager::controllerView() const
{
    return d->controllerView;
}

QGraphicsView *AcViewManager::pitchView() const
{
    return d->pitchView;
}

QGraphicsView *AcViewManager::timeView() const
{
    return d->timeView;
}

qreal AcViewManager::positionX() const
{
    return d->scoreView->center().x();
}

void AcViewManager::setPositionX(qreal positionX)
{
    d->scoreView->setCenter(positionX, positionY());
}

qreal AcViewManager::positionY() const
{
    return d->scoreView->center().y();
}

void AcViewManager::setPositionY(qreal positionY)
{
    d->scoreView->setCenter(positionX(), positionY);
}

qreal AcViewManager::scaleX() const
{
    return AcScore::instance()->viewSettings()->scaleX();
}

void AcViewManager::setScaleX(qreal scaleX)
{
    AcScore::instance()->viewSettings()->setScaleX(scaleX);
}

qreal AcViewManager::scaleY() const
{
    return AcScore::instance()->viewSettings()->scaleY();
}

void AcViewManager::setScaleY(qreal scaleY)
{
    AcScore::instance()->viewSettings()->setScaleY(scaleY);
}

void AcViewManager::updateViews()
{
    d->scoreView->updateTransform();
    d->updateViewCenters();
}

void AcViewManager::updateViewSettingsProperty(const QString &propertyName)
{
    if (propertyName.startsWith("position"))
        d->updateViewCenters();
    else if (propertyName.startsWith("scale")) {
        d->scoreView->updateTransform();
        d->updateViewCenters();
    }
}
