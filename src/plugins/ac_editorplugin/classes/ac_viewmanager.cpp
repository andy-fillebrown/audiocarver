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
#include <ac_controllerscene.h>
#include <ac_controllerview.h>
#include <ac_pitchscene.h>
#include <ac_pitchview.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_scoreview.h>
#include <ac_timescene.h>
#include <ac_timeview.h>
#include <ac_viewsettings.h>
#include <QWidget>

using namespace Private;

namespace Private {

class AcViewManagerData
{
public:
    AcViewManager *q;
    QWidget *widget;
    AcScoreScene *scoreScene;
    AcScoreView *scoreView;
    AcControllerScene *controllerScene;
    AcControllerView *controllerView;
    AcPitchScene *pitchScene;
    AcPitchView *pitchView;
    AcTimeScene *timeScene;
    AcTimeView *timeView;
    AcScore *score;
    AcViewSettings *viewSettings;

    AcViewManagerData(AcViewManager *q, QWidget *widget)
        :   q(q)
        ,   widget(widget)
        ,   scoreScene(new AcScoreScene(q))
        ,   scoreView(new AcScoreView(scoreScene, widget))
        ,   controllerScene(new AcControllerScene(q))
        ,   controllerView(new AcControllerView(controllerScene, widget))
        ,   pitchScene(new AcPitchScene(q))
        ,   pitchView(new AcPitchView(pitchScene, widget))
        ,   timeScene(new AcTimeScene(q))
        ,   timeView(new AcTimeView(timeScene, widget))
        ,   score(AcScore::instance())
        ,   viewSettings(score->viewSettings())
    {}
};

} // namespace Private

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerData(this, widget))
{
    connect(d->score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
    connect(d->viewSettings, SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
}

AcViewManager::~AcViewManager()
{
    delete d;
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
    return d->viewSettings->scaleX();
}

void AcViewManager::setScaleX(qreal scaleX)
{
    d->viewSettings->setScaleX(scaleX);
}

qreal AcViewManager::scaleY() const
{
    return d->viewSettings->scaleY();
}

void AcViewManager::setScaleY(qreal scaleY)
{
    d->viewSettings->setScaleY(scaleY);
}

void AcViewManager::updateScoreProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}

void AcViewManager::updateViewSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}

AcScoreView *AcViewManager::scoreView() const
{
    return d->scoreView;
}

AcControllerView *AcViewManager::controllerView() const
{
    return d->controllerView;
}

AcPitchView *AcViewManager::pitchView() const
{
    return d->pitchView;
}

AcTimeView *AcViewManager::timeView() const
{
    return d->timeView;
}

void AcViewManager::updateViews()
{
}
