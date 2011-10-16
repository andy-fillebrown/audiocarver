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

#include "ac_graphicsscene.h"

#include <ac_model.h>

class SceneManagerPrivate
{
public:
    SceneManager *q;
    Model *model;
    PitchScene *pitchScene;
    ControlScene *controlScene;
    TimeLabelScene *timeLabelScene;
    PitchLabelScene *pitchLabelScene;
    ControlLabelScene *controlLabelScene;

    SceneManagerPrivate(SceneManager *q)
        :   q(q)
        ,   model(0)
        ,   pitchScene(0)
        ,   controlScene(0)
        ,   timeLabelScene(0)
        ,   pitchLabelScene(0)
        ,   controlLabelScene(0)
    {}

    void init()
    {
        pitchScene = new PitchScene(q);
        controlScene = new ControlScene(q);
        timeLabelScene = new TimeLabelScene(q);
        pitchLabelScene = new PitchLabelScene(q);
        controlLabelScene = new ControlLabelScene(q);
    }

    virtual ~SceneManagerPrivate()
    {
        delete model;
    }
};

static SceneManager *instance = 0;

SceneManager::SceneManager(QObject *parent)
    :   QObject(parent)
    ,   d(new SceneManagerPrivate(this))
{
    d->init();
    ::instance = this;
}

SceneManager::~SceneManager()
{
    delete d;
}

SceneManager *SceneManager::instance()
{
    return ::instance;
}

Model *SceneManager::model() const
{
    return d->model;
}

void SceneManager::setModel(Model *model)
{
    if (d->model == model)
        return;
    if (d->model) {
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            Ac::SceneType type = Ac::SceneType(i);
            scene(type)->removeItem(d->model->sceneItem(type));
        }
    }
    d->model = model;
    if (d->model) {
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            Ac::SceneType type = Ac::SceneType(i);
            scene(type)->addItem(d->model->sceneItem(type));
        }
    }
}

QGraphicsScene *SceneManager::scene(Ac::SceneType type)
{
    switch (type) {
    case Ac::PitchScene:
        return d->pitchScene;
    case Ac::ControlScene:
        return d->controlScene;
    case Ac::TimeLabelScene:
        return d->timeLabelScene;
    case Ac::PitchLabelScene:
        return d->pitchLabelScene;
    case Ac::ControlLabelScene:
        return d->controlLabelScene;
    default:
        return 0;
    }
}
