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
#include <ac_undo.h>

#include <ac_coreconstants.h>
#include <ac_model.h>

#include <mi_idatabase.h>
#include <mi_ieditor.h>

#include <QWidget>

#include <QTimer>

static bool fuzzyCompare(qreal a, qreal b)
{
//    return qFuzzyCompare(float(a), float(b));
    return qFuzzyCompare(a, b);
}

class ViewManagerPrivate
{
public:
    ViewManager *q;
    SceneManager *sceneManager;
    PitchView *pitchView;
    ControlView *controlView;
    TimeLabelView *timeLabelView;
    PitchLabelView *pitchLabelView;
    ControlLabelView *controlLabelView;
    Model *model;
    qreal scoreLength;
    qreal timePos;
    qreal pitchPos;
    qreal controlPos;
    qreal timeScale;
    qreal pitchScale;
    qreal controlScale;
    quint32 initialized : 1;
    quint32 updatingDatabase : 31;
    UndoViewSettingsCommand *undoCmd;

    ViewManagerPrivate(ViewManager *q)
        :   q(q)
        ,   sceneManager(new SceneManager(q))
        ,   pitchView(0)
        ,   controlView(0)
        ,   timeLabelView(0)
        ,   pitchLabelView(0)
        ,   controlLabelView(0)
        ,   model(interfaceToObject_cast<Model>(IDatabase::instance()->model()))
        ,   initialized(quint32(false))
        ,   updatingDatabase(quint32(false))
        ,   undoCmd(0)
    {}

    void init()
    {
        QWidget *widget = object_cast<QWidget>(q->parent());
        pitchView = new PitchView(sceneManager->scene(Ac::PitchScene), widget);
        controlView = new ControlView(sceneManager->scene(Ac::ControlScene), widget);
        timeLabelView = new TimeLabelView(sceneManager->scene(Ac::TimeLabelScene), widget);
        pitchLabelView = new PitchLabelView(sceneManager->scene(Ac::PitchLabelScene), widget);
        controlLabelView = new ControlLabelView(sceneManager->scene(Ac::ControlLabelScene), widget);

        q->connect(q, SIGNAL(viewPositionChanged(int)), pitchView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), controlView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), timeLabelView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), pitchLabelView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), controlLabelView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), pitchView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), controlView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), timeLabelView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), pitchLabelView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), controlLabelView, SLOT(viewScaleChanged(int)));

        IDatabase *db = IDatabase::instance();
        q->connect(db, SIGNAL(databaseAboutToBeRead()), q, SLOT(databaseAboutToBeRead()));
        q->connect(db, SIGNAL(databaseRead()), q, SLOT(databaseRead()));
        q->connect(db, SIGNAL(databaseAboutToBeWritten()), q, SLOT(databaseAboutToBeWritten()));

        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), q, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pitchView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), controlView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), timeLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pitchLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), controlLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(modelAboutToBeReset()), q, SLOT(disableUpdates()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), pitchView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), controlView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), timeLabelView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), pitchLabelView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), controlLabelView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelReset()), q, SLOT(modelReset()));

        updateViewVariables();
        q->updateViews();

        initialized = true;
    }

    ~ViewManagerPrivate()
    {
        delete undoCmd;
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
        const qreal modelScoreLength = model->data(QModelIndex(), Ac::LengthRole).toReal();
        if (scoreLength != modelScoreLength) {
            scoreLength = modelScoreLength;
            emit q->scoreLengthChanged();
        }

        const QModelIndex viewSettings = model->itemIndex(Ac::ViewSettingsItem);
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

    void startUndo()
    {
        if (!undoCmd
                && initialized
                && !IDatabase::instance()->isReading()
                && IEditor::instance()->canPushCommand())
            undoCmd = new UndoViewSettingsCommand;
    }

    void finishUndo()
    {
        if (undoCmd) {
            IEditor::instance()->pushCommand(undoCmd);
            undoCmd = 0;
        }
    }
};

static ViewManager *instance = 0;

ViewManager::ViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new ViewManagerPrivate(this))
{
    ::instance = this;
    d->init();
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

qreal ViewManager::scoreLength() const
{
    return d->scoreLength;
}

qreal ViewManager::position(int role) const
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

void ViewManager::setPosition(qreal position, int role)
{
    switch (role) {
    case Ac::TimePositionRole:
        position = qBound(qreal(0.0f), position, d->scoreLength);
        if (fuzzyCompare(d->timePos, position))
            return;
        d->startUndo();
        d->timePos = position;
        emit viewPositionChanged(Ac::TimePositionRole);
        break;
    case Ac::PitchPositionRole:
        position = qBound(qreal(0.0f), position, qreal(127.0f));
        if (fuzzyCompare(d->pitchPos, position))
            return;
        d->startUndo();
        d->pitchPos = position;
        emit viewPositionChanged(Ac::PitchPositionRole);
        break;
    case Ac::ControlPositionRole:
        position = qBound(qreal(0.0f), position, qreal(1.0f));
        if (fuzzyCompare(d->controlPos, position))
            return;
        d->startUndo();
        d->controlPos = position;
        emit viewPositionChanged(Ac::ControlPositionRole);
    default:
        break;
    }
}

qreal ViewManager::scale(int role) const
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

void ViewManager::setScale(qreal scale, int role)
{
    if (scale < VIEWSCALE_MIN)
        scale = VIEWSCALE_MIN;
    if (fuzzyCompare(this->scale(role), scale))
        return;
    switch (role) {
    case Ac::TimeScaleRole:
        d->startUndo();
        d->timeScale = scale;
        emit viewScaleChanged(Ac::TimeScaleRole);
        break;
    case Ac::PitchScaleRole:
        d->startUndo();
        d->pitchScale = scale;
        emit viewScaleChanged(Ac::PitchScaleRole);
        break;
    case Ac::ControlScaleRole:
        d->startUndo();
        d->controlScale = scale;
        emit viewScaleChanged(Ac::ControlScaleRole);
    default:
        break;
    }
}

void ViewManager::updateDatabase()
{
    IModel *m = IDatabase::instance()->model();
    const QModelIndex viewSettings = m->itemIndex(Ac::ViewSettingsItem);
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
    if (d->pitchView->isDirty())
        d->pitchView->updateView();
    if (d->controlView->isDirty())
        d->controlView->updateView();
    if (d->timeLabelView->isDirty())
        d->timeLabelView->updateView();
    if (d->pitchLabelView->isDirty())
        d->pitchLabelView->updateView();
    if (d->controlLabelView->isDirty())
        d->controlLabelView->updateView();
    d->finishUndo();
}

void ViewManager::databaseAboutToBeRead()
{
    disableUpdates();
    d->clearViewVariables();
}

void ViewManager::databaseRead()
{
    d->updateViewVariables();
    d->emitAllViewSettingsChanged();
    enableUpdates();
    updateViews();
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
                || IDatabase::instance()->model()->itemIndex(Ac::ViewSettingsItem) == topRight))
        d->updateViewVariables();
}

void ViewManager::modelReset()
{
    d->clearViewVariables();
    enableUpdates();
}
