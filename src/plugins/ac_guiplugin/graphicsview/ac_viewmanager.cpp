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

#include <ac_pitchlabelview.h>
#include <ac_pitchview.h>
#include <ac_graphicsscene.h>
#include <ac_timelabelview.h>
#include <ac_volumelabelview.h>
#include <ac_volumeview.h>

#include <ac_model.h>

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
        ,   sceneManager(new SceneManager(q))
        ,   pitchView(new AcPitchView(sceneManager->scene(Ac::PitchScene), widget))
        ,   controlView(new AcVolumeView(sceneManager->scene(Ac::ControlScene), widget))
        ,   timeLabelView(new AcTimeLabelView(sceneManager->scene(Ac::TimeLabelScene), widget))
        ,   pitchLabelView(new AcPitchLabelView(sceneManager->scene(Ac::PitchLabelScene), widget))
        ,   controlLabelView(new AcVolumeLabelView(sceneManager->scene(Ac::ControlLabelScene), widget))
    {}

    void updateScoreLength()
    {
        Model *model = sceneManager->model();
        qreal scoreLength = model ? model->data(QModelIndex(), Ac::LengthRole).toReal() : 0;
        pitchView->setSceneRect(0, 0, scoreLength, -127);
        qreal width = pitchView->width();
        qreal x = width / scoreLength;
        qreal y = qreal(pitchView->height()) / 127.0f;
        pitchView->setTransform(QTransform::fromScale(x, y));
//        controlView->setSceneRect(0, 0, scoreLength, 1);
//        timeLabelView->setSceneRect(0, 0, scoreLength, 1);
    }
};

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerPrivate(this, widget))
{}

AcViewManager::~AcViewManager()
{
    delete d;
}

QGraphicsView *AcViewManager::view(Ac::SceneType type) const
{
    switch (type) {
    case Ac::PitchScene: return d->pitchView;
    case Ac::ControlScene: return d->controlView;
    case Ac::TimeLabelScene: return d->timeLabelView;
    case Ac::PitchLabelScene: return d->pitchLabelView;
    case Ac::ControlLabelScene: return d->controlLabelView;
    default: return 0;
    }
}

void AcViewManager::setModel(Model *model)
{
    Model *oldModel = d->sceneManager->model();
    d->sceneManager->setModel(model);
    if (oldModel == model)
        return;
    if (oldModel)
        oldModel->disconnect(this);
    if (model) {
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
        d->updateScoreLength();
    }
}

void AcViewManager::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    Q_UNUSED(bottomLeft);
    if (!topRight.isValid())
        d->updateScoreLength();
}
