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

#include <ac_model.h>

#include <QWidget>

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

    ViewManagerPrivate(ViewManager *q, QWidget *widget)
        :   q(q)
        ,   sceneManager(new SceneManager(q))
        ,   pitchView(new PitchView(sceneManager->scene(Ac::PitchScene), widget))
        ,   controlView(new ControlView(sceneManager->scene(Ac::ControlScene), widget))
        ,   timeLabelView(new TimeLabelView(sceneManager->scene(Ac::TimeLabelScene), widget))
        ,   pitchLabelView(new PitchLabelView(sceneManager->scene(Ac::PitchLabelScene), widget))
        ,   controlLabelView(new ControlLabelView(sceneManager->scene(Ac::ControlLabelScene), widget))
    {}
};

ViewManager::ViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new ViewManagerPrivate(this, widget))
{
    connect(this, SIGNAL(scoreDataChanged()), d->pitchView, SLOT(scoreDataChanged()));
    connect(this, SIGNAL(scoreDataChanged()), d->controlView, SLOT(scoreDataChanged()));
    connect(this, SIGNAL(scoreDataChanged()), d->timeLabelView, SLOT(scoreDataChanged()));
}

ViewManager::~ViewManager()
{
    delete d;
}

QGraphicsView *ViewManager::view(Ac::SceneType type) const
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

void ViewManager::setModel(Model *model)
{
    Model *oldModel = d->sceneManager->model();
    d->sceneManager->setModel(model);
    if (oldModel == model)
        return;
    if (oldModel)
        oldModel->disconnect(this);
    if (model) {
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
        emit scoreDataChanged();
    }
}

void ViewManager::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    Q_UNUSED(bottomLeft);
    if (!topRight.isValid())
        emit scoreDataChanged();
}
