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

#include <ac_controllabelview.h>
#include <ac_controlview.h>
#include <ac_graphicsscene.h>
#include <ac_pitchlabelview.h>
#include <ac_pitchview.h>
#include <ac_timelabelview.h>

#include <ac_coreconstants.h>
#include <ac_model.h>

#include <QWidget>

class ViewManagerPrivate
{
public:
    ViewManager *q;
    QWidget *parentWidget;
    SceneManager *sceneManager;
    PitchView *pitchView;
    ControlView *controlView;
    TimeLabelView *timeLabelView;
    PitchLabelView *pitchLabelView;
    ControlLabelView *controlLabelView;
    qreal scoreLength;
    qreal timePos;
    qreal pitchPos;
    qreal controlPos;
    qreal timeScale;
    qreal pitchScale;
    qreal controlScale;
    int updatingViewSettings : 1;
    int updatesEnabled : 31;

    ViewManagerPrivate(ViewManager *q, QWidget *parentWidget)
        :   q(q)
        ,   parentWidget(parentWidget)
        ,   sceneManager(new SceneManager(q))
        ,   pitchView(0)
        ,   controlView(0)
        ,   timeLabelView(0)
        ,   pitchLabelView(0)
        ,   controlLabelView(0)
        ,   updatingViewSettings(false)
        ,   updatesEnabled(true)
    {}

    void init()
    {
        pitchView = new PitchView(sceneManager->scene(Ac::PitchScene), parentWidget);
        controlView = new ControlView(sceneManager->scene(Ac::ControlScene), parentWidget);
        timeLabelView = new TimeLabelView(sceneManager->scene(Ac::TimeLabelScene), parentWidget);
        pitchLabelView = new PitchLabelView(sceneManager->scene(Ac::PitchLabelScene), parentWidget);
        controlLabelView = new ControlLabelView(sceneManager->scene(Ac::ControlLabelScene), parentWidget);
    }

    void clearViewVariables()
    {
        scoreLength = -1.0f;
        timePos = 0;
        pitchPos = 0;
        controlPos = 0;
        timeScale = -1.0f;
        pitchScale = -1.0f;
        controlScale = -1.0f;
        emit q->viewSettingsChanged();
        emit q->viewScaleChanged(Ac::TimeScaleRole);
        emit q->viewScaleChanged(Ac::PitchScaleRole);
        emit q->viewScaleChanged(Ac::ControlScaleRole);
    }

    void updateViewVariables()
    {
        Model *model = sceneManager->model();
        QModelIndex viewSettings = model->viewSettingsIndex();
        qreal modelScoreLength = model->data(QModelIndex(), Ac::LengthRole).toReal();
        qreal modelTimePos = viewSettings.data(Ac::TimePositionRole).toReal();
        qreal modelPitchPos = viewSettings.data(Ac::PitchPositionRole).toReal();
        qreal modelControlPos = viewSettings.data(Ac::ControlPositionRole).toReal();
        qreal modelTimeScale = viewSettings.data(Ac::TimeScaleRole).toReal();
        qreal modelPitchScale = viewSettings.data(Ac::PitchScaleRole).toReal();
        qreal modelControlScale = viewSettings.data(Ac::ControlScaleRole).toReal();
        bool timeScaleChanged = timeScale != modelTimeScale;
        bool pitchScaleChanged = pitchScale != modelPitchScale;
        bool controlScaleChanged = controlScale != modelControlScale;
        bool changed = scoreLength != modelScoreLength
                || timePos != modelTimePos
                || pitchPos != modelPitchPos
                || controlPos != modelControlPos
                || timeScaleChanged
                || pitchScaleChanged
                || controlScaleChanged;
        scoreLength = modelScoreLength;
        timePos = modelTimePos;
        pitchPos = modelPitchPos;
        controlPos = modelControlPos;
        timeScale = modelTimeScale;
        pitchScale = modelPitchScale;
        controlScale = modelControlScale;
        if (changed)
            emit q->viewSettingsChanged();
        if (timeScaleChanged)
            emit q->viewScaleChanged(Ac::TimeScaleRole);
        if (pitchScaleChanged)
            emit q->viewScaleChanged(Ac::PitchScaleRole);
        if (controlScaleChanged)
            emit q->viewScaleChanged(Ac::ControlScaleRole);
    }
};

static ViewManager *instance = 0;

ViewManager::ViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new ViewManagerPrivate(this, widget))
{
    ::instance = this;
    d->init();
    connect(this, SIGNAL(viewSettingsChanged()), d->pitchView, SLOT(viewSettingsChanged()));
    connect(this, SIGNAL(viewSettingsChanged()), d->controlView, SLOT(viewSettingsChanged()));
    connect(this, SIGNAL(viewSettingsChanged()), d->timeLabelView, SLOT(viewSettingsChanged()));
    connect(this, SIGNAL(viewScaleChanged(int)), d->timeLabelView, SLOT(viewScaleChanged(int)));
    connect(this, SIGNAL(viewSettingsChanged()), d->pitchLabelView, SLOT(viewSettingsChanged()));
    connect(this, SIGNAL(viewScaleChanged(int)), d->pitchLabelView, SLOT(viewScaleChanged(int)));
    connect(this, SIGNAL(viewSettingsChanged()), d->controlLabelView, SLOT(viewSettingsChanged()));
    connect(this, SIGNAL(viewScaleChanged(int)), d->controlLabelView, SLOT(viewScaleChanged(int)));
}

ViewManager::~ViewManager()
{
    delete d;
}

ViewManager *ViewManager::instance()
{
    return ::instance;
}

QGraphicsView *ViewManager::view(int type) const
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

Model *ViewManager::model() const
{
    return d->sceneManager->model();
}

void ViewManager::setModel(Model *model)
{
    Model *oldModel = d->sceneManager->model();
    d->sceneManager->setModel(model);
    if (oldModel == model)
        return;
    if (oldModel) {
        oldModel->disconnect(this);
        oldModel->disconnect(d->pitchView);
        oldModel->disconnect(d->controlView);
        oldModel->disconnect(d->timeLabelView);
        oldModel->disconnect(d->pitchLabelView);
        oldModel->disconnect(d->controlLabelView);
    }
    if (model) {
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d->timeLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d->pitchLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d->controlLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(model, SIGNAL(modelAboutToBeReset()), d->pitchView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->controlView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->timeLabelView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->pitchLabelView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->controlLabelView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
        d->updateViewVariables();
    }
}

qreal ViewManager::scoreLength() const
{
    return d->scoreLength;
}

qreal ViewManager::position(Ac::ItemDataRole role) const
{
    switch (role) {
    case Ac::TimePositionRole:
        return d->timePos;
    case Ac::PitchPositionRole:
        return d->pitchPos;
    case Ac::ControlPositionRole:
        return d->controlPos;
    default:
        return 0.0f;
    }
}

void ViewManager::setPosition(qreal position, Ac::ItemDataRole role)
{
    switch (role) {
    case Ac::TimePositionRole:
        position = qBound(qreal(0.0f), position, d->scoreLength);
        d->timePos = position;
        break;
    case Ac::PitchPositionRole:
        position = qBound(qreal(0.0f), position, qreal(127.0f));
        d->pitchPos = position;
        break;
    case Ac::ControlPositionRole:
        position = qBound(qreal(0.0f), position, qreal(1.0f));
        d->controlPos = position;
    default:
        break;
    }
}

qreal ViewManager::scale(Ac::ItemDataRole role) const
{
    switch (role) {
    case Ac::TimeScaleRole:
        return d->timeScale;
    case Ac::PitchScaleRole:
        return d->pitchScale;
    case Ac::ControlScaleRole:
        return d->controlScale;
    default:
        return 1.0f;
    }
}

void ViewManager::setScale(qreal scale, Ac::ItemDataRole role)
{
    if (scale < VIEWSCALE_MIN)
        scale = VIEWSCALE_MIN;
    if (this->scale(role) == scale)
        return;
    switch (role) {
    case Ac::TimeScaleRole:
        d->timeScale = scale;
        break;
    case Ac::PitchScaleRole:
        d->pitchScale = scale;
        break;
    case Ac::ControlScaleRole:
        d->controlScale = scale;
    default:
        break;
    }
}

void ViewManager::updateViewSettings()
{
    Model *m = model();
    QModelIndex viewSettings = m->viewSettingsIndex();
    d->updatingViewSettings = true;
    m->setData(viewSettings, d->timePos, Ac::TimePositionRole);
    m->setData(viewSettings, d->pitchPos, Ac::PitchPositionRole);
    m->setData(viewSettings, d->controlPos, Ac::ControlPositionRole);
    m->setData(viewSettings, d->timeScale, Ac::TimeScaleRole);
    m->setData(viewSettings, d->pitchScale, Ac::PitchScaleRole);
    m->setData(viewSettings, d->controlScale, Ac::ControlScaleRole);
    d->updatingViewSettings = false;
}

void ViewManager::setUpdatesEnabled(bool enable)
{
    if (d->updatesEnabled == enable)
        return;
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsView *v = view(i);
        v->setViewportUpdateMode(enable ? QGraphicsView::MinimalViewportUpdate : QGraphicsView::NoViewportUpdate);
        v->setUpdatesEnabled(enable);
    }
    d->updatesEnabled = enable;
}

void ViewManager::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    Q_UNUSED(bottomLeft);
    if (!d->updatingViewSettings
            && (!topRight.isValid()
                || model()->viewSettingsIndex() == topRight))
        d->updateViewVariables();
}

void ViewManager::modelReset()
{
    d->clearViewVariables();
}
