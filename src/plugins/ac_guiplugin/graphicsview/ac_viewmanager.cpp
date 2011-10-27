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

#include <mi_idatabase.h>

#include <QWidget>

#include <QTimer>

static bool fuzzyCompare(qreal a, qreal b)
{
    return qFuzzyCompare(float(a), float(b));
}

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
    quint32 databaseReading : 1;
    quint32 updatingDatabase : 31;

    ViewManagerPrivate(ViewManager *q, QWidget *parentWidget)
        :   q(q)
        ,   parentWidget(parentWidget)
        ,   sceneManager(new SceneManager(q))
        ,   pitchView(0)
        ,   controlView(0)
        ,   timeLabelView(0)
        ,   pitchLabelView(0)
        ,   controlLabelView(0)
        ,   databaseReading(quint32(false))
        ,   updatingDatabase(quint32(false))
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
        emitAllViewSettingsChanged();
    }

    void updateViewVariables()
    {
        const Model *model = sceneManager->model();
        const QModelIndex viewSettings = model->viewSettingsIndex();
        const qreal modelScoreLength = model->data(QModelIndex(), Ac::LengthRole).toReal();
        if (scoreLength != modelScoreLength) {
            scoreLength = modelScoreLength;
            emit q->scoreLengthChanged();
        }
        q->setPosition(viewSettings.data(Ac::TimePositionRole).toReal(), Ac::TimePositionRole);
        q->setPosition(viewSettings.data(Ac::PitchPositionRole).toReal(), Ac::PitchPositionRole);
        q->setPosition(viewSettings.data(Ac::ControlPositionRole).toReal(), Ac::ControlPositionRole);
        q->setScale(viewSettings.data(Ac::TimeScaleRole).toReal(), Ac::TimeScaleRole);
        q->setScale(viewSettings.data(Ac::PitchScaleRole).toReal(), Ac::PitchScaleRole);
        q->setScale(viewSettings.data(Ac::ControlScaleRole).toReal(), Ac::ControlScaleRole);
    }

    void emitAllViewSettingsChanged()
    {
        emit q->viewPositionChanged(Ac::TimePositionRole);
        emit q->viewPositionChanged(Ac::PitchPositionRole);
        emit q->viewPositionChanged(Ac::ControlPositionRole);
        emit q->viewScaleChanged(Ac::TimeScaleRole);
        emit q->viewScaleChanged(Ac::PitchScaleRole);
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
    IDatabase *db = IDatabase::instance();
    connect(db, SIGNAL(databaseAboutToBeRead()), SLOT(databaseAboutToBeRead()));
    connect(db, SIGNAL(databaseRead()), SLOT(databaseRead()));
    connect(db, SIGNAL(databaseAboutToBeWritten()), SLOT(databaseAboutToBeWritten()));
    connect(this, SIGNAL(viewPositionChanged(int)), d->pitchView, SLOT(viewPositionChanged(int)));
    connect(this, SIGNAL(viewPositionChanged(int)), d->controlView, SLOT(viewPositionChanged(int)));
    connect(this, SIGNAL(viewPositionChanged(int)), d->timeLabelView, SLOT(viewPositionChanged(int)));
    connect(this, SIGNAL(viewPositionChanged(int)), d->pitchLabelView, SLOT(viewPositionChanged(int)));
    connect(this, SIGNAL(viewPositionChanged(int)), d->controlLabelView, SLOT(viewPositionChanged(int)));
    connect(this, SIGNAL(viewScaleChanged(int)), d->pitchView, SLOT(viewScaleChanged(int)));
    connect(this, SIGNAL(viewScaleChanged(int)), d->controlView, SLOT(viewScaleChanged(int)));
    connect(this, SIGNAL(viewScaleChanged(int)), d->timeLabelView, SLOT(viewScaleChanged(int)));
    connect(this, SIGNAL(viewScaleChanged(int)), d->pitchLabelView, SLOT(viewScaleChanged(int)));
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
        connect(model, SIGNAL(modelAboutToBeReset()), SLOT(disableUpdates()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->pitchView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->controlView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->timeLabelView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->pitchLabelView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelAboutToBeReset()), d->controlLabelView, SLOT(modelAboutToBeReset()));
        connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
        d->updateViewVariables();
        updateViews();
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
        if (fuzzyCompare(d->timePos, position))
            return;
        d->timePos = position;
        emit viewPositionChanged(Ac::TimePositionRole);
        break;
    case Ac::PitchPositionRole:
        position = qBound(qreal(0.0f), position, qreal(127.0f));
        if (fuzzyCompare(d->pitchPos, position))
            return;
        d->pitchPos = position;
        emit viewPositionChanged(Ac::PitchPositionRole);
        break;
    case Ac::ControlPositionRole:
        position = qBound(qreal(0.0f), position, qreal(1.0f));
        if (fuzzyCompare(d->controlPos, position))
            return;
        d->controlPos = position;
        emit viewPositionChanged(Ac::ControlPositionRole);
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
    if (fuzzyCompare(this->scale(role), scale))
        return;
    switch (role) {
    case Ac::TimeScaleRole:
        d->timeScale = scale;
        emit viewScaleChanged(Ac::TimeScaleRole);
        break;
    case Ac::PitchScaleRole:
        d->pitchScale = scale;
        emit viewScaleChanged(Ac::PitchScaleRole);
        break;
    case Ac::ControlScaleRole:
        d->controlScale = scale;
        emit viewScaleChanged(Ac::ControlScaleRole);
    default:
        break;
    }
}

void ViewManager::updateDatabase()
{
    Model *m = model();
    const QModelIndex viewSettings = m->viewSettingsIndex();
    d->updatingDatabase = true;
    m->setData(viewSettings, d->timePos, Ac::TimePositionRole);
    m->setData(viewSettings, d->pitchPos, Ac::PitchPositionRole);
    m->setData(viewSettings, d->controlPos, Ac::ControlPositionRole);
    m->setData(viewSettings, d->timeScale, Ac::TimeScaleRole);
    m->setData(viewSettings, d->pitchScale, Ac::PitchScaleRole);
    m->setData(viewSettings, d->controlScale, Ac::ControlScaleRole);
    d->updatingDatabase = false;
}

void ViewManager::updateViews()
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
        view(i)->update();
}

bool ViewManager::databaseIsReading() const
{
    return d->databaseReading;
}

void ViewManager::databaseAboutToBeRead()
{
    d->databaseReading = true;
    disableUpdates();
    d->clearViewVariables();
}

void ViewManager::databaseRead()
{
    d->updateViewVariables();
    d->databaseReading = false;
    d->emitAllViewSettingsChanged();
    enableUpdates();
}

void ViewManager::databaseAboutToBeWritten()
{
    updateDatabase();
}

void ViewManager::disableUpdates()
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
        view(i)->setUpdatesEnabled(false);
}

void ViewManager::enableUpdates()
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
        view(i)->setUpdatesEnabled(true);
}

void ViewManager::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    Q_UNUSED(bottomLeft);
    if (!d->updatingDatabase
            && (!topRight.isValid()
                || model()->viewSettingsIndex() == topRight))
        d->updateViewVariables();
}

void ViewManager::modelReset()
{
    d->clearViewVariables();
    enableUpdates();
}
