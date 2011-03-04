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

#include "trackscene.h"

#include "notescene.h"
#include "scorescene.h"

#include <databaseplugin/classes/object.h>

#include <ac_databaseplugin/classes/track.h>

using namespace AudioCarver;
using namespace Internal;

namespace AudioCarver {
namespace Internal {

class TrackScenePrivate
{
public:
    TrackScene *q;
    ScoreScene *scoreScene;
    Track *track;
    QList<NoteScene*> notes;

    TrackScenePrivate(TrackScene *q, ScoreScene *scoreScene)
        :   q(q)
        ,   scoreScene(scoreScene)
        ,   track(qobject_cast<Track*>(q->databaseObject()))
    {
        Q_ASSERT(scoreScene);
        Q_ASSERT(track);
    }

    ~TrackScenePrivate()
    {
        track = 0;
        scoreScene = 0;
        q = 0;
    }

    void updateNotes()
    {
        ac_updateSceneList_helper(notes, track->notes()->data(), q);
    }
};

} // namespace Internal
} // namespace AudioCarver

TrackScene::TrackScene(Database::Object *databaseObject, QObject *parent)
    :   SceneObject(databaseObject, parent)
    ,   d(new TrackScenePrivate(this, qobject_cast<ScoreScene*>(parent)))
{
    Q_CHECK_PTR(d);
}

TrackScene::~TrackScene()
{
    delete d;  d = 0;
}

void TrackScene::updateProperty(int index)
{
    const QString propertyName = databaseObject()->propertyName(index);

    if (propertyName == "notes") {
        d->updateNotes();
        return;
    }

    SceneObject::updateProperty(index);
}
