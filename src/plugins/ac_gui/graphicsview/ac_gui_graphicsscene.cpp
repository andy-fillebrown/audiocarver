/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_gui_graphicsscene.h"
#include <ientity.h>
#include <idatabase.h>
#include <imodel.h>
#include <imodelitem.h>

static SceneManager *instance = 0;

class SceneManagerPrivate
{
public:
    SceneManager *q;
    PitchScene *pitchScene;
    ControlScene *controlScene;
    TimeLabelScene *timeLabelScene;
    PitchLabelScene *pitchLabelScene;
    ControlLabelScene *controlLabelScene;

    SceneManagerPrivate(SceneManager *q)
        :   q(q)
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

        // Add the root entity's graphics items to the scenes.
        IEntity *root_entity = query<IEntity>(IDatabase::instance()->rootItem());
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            QGraphicsScene *scene = q->scene(i);
            for (int j = 0;  j < Ac::TransformTypeCount;  ++j)
                scene->addItem(root_entity->graphicsItem(i, j));
        }
    }
};

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

QGraphicsScene *SceneManager::scene(int type)
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
