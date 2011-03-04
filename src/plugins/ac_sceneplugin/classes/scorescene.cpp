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

#include "scorescene.h"

#include <classes/fcurvescene.h>
#include <classes/trackscene.h>

#include <ac_databaseplugin/classes/score.h>

#include <databaseplugin/classes/list.h>

#include <QtCore/QPair>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class ScoreScenePrivate
{
public:
    ScoreScene *q;
    Score *score;
    QList<FCurveScene*> curves;
    QList<TrackScene*> tracks;

    ScoreScenePrivate(ScoreScene *q)
        :   q(q)
        ,   score(Score::instance())
    {
    }

    ~ScoreScenePrivate()
    {
    }

    void updateCurves()
    {
        ac_updateSceneList_helper(curves, score->curves()->data(), q);
    }

    void updateTracks()
    {
        ac_updateSceneList_helper(tracks, score->tracks()->data(), q);
    }
};

} // Internal
} // AudioCarver

ScoreScene::ScoreScene(QObject *parent)
    :   SceneObject(Score::instance(), parent)
    ,   d(new Internal::ScoreScenePrivate(this))
{
}

ScoreScene::~ScoreScene()
{
}

void ScoreScene::updateProperty(int index)
{
    const QString propertyName = d->score->propertyName(index);

    if (propertyName == "curves") {
        d->updateCurves();
        return;
    }

    if (propertyName == "tracks") {
        d->updateTracks();
        return;
    }

    SceneObject::updateProperty(index);
}
