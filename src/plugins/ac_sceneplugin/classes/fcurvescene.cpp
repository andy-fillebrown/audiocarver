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

#include "fcurvescene.h"

#include "notescene.h"
#include "scorescene.h"

#include <ac_databaseplugin/classes/fcurve.h>
#include <ac_databaseplugin/classes/note.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class FCurveScenePrivate
{
public:
    FCurveScene *q;
    ScoreScene *scoreScene;
    FCurve *curve;
    QList<NoteScene*> linkedNotes;
    int pointCount;

    FCurveScenePrivate(FCurveScene *q, ScoreScene *scoreScene)
        :   q(q)
        ,   scoreScene(scoreScene)
        ,   curve(qobject_cast<FCurve*>(q->databaseObject()))
        ,   pointCount(64)
    {
        Q_ASSERT(scoreScene);
        Q_ASSERT(curve);
    }

    ~FCurveScenePrivate()
    {
        curve = 0;
        scoreScene = 0;
        q = 0;
    }

    void updatePointCount()
    {
        // Find max point count.  If less than pointCount, update VBO.
        // Assumes maxCount will be less than or equal to pointCount, i.e. when
        // removing a linked note.

        int maxCount = 0;

        foreach (NoteScene *note, linkedNotes) {
            Note *db_note = qobject_cast<Note*>(note->databaseObject());
            Q_ASSERT(db_note);

            if (maxCount < db_note->pointCount())
                maxCount = db_note->pointCount();
        }

        if (maxCount < pointCount) {
            pointCount = maxCount;
            q->updateVBO();
        }
    }
};

} // Internal
} // AudioCarver

FCurveScene::FCurveScene(Database::Object *databaseObject, QObject *parent)
    :   SceneObject(databaseObject, parent)
    ,   d(new FCurveScenePrivate(this, qobject_cast<ScoreScene*>(parent)))
{
    Q_CHECK_PTR(d);

    d->curve = qobject_cast<FCurve*>(databaseObject);
    Q_ASSERT(d->curve);

    connect(d->curve, SIGNAL(pointsChanged()), SLOT(updateVBO()));
}

FCurveScene::~FCurveScene()
{
    delete d;  d = 0;
}

void FCurveScene::appendNote(NoteScene *note)
{
    if (!d->linkedNotes.contains(note)) {
        d->linkedNotes.append(note);

        Note *db_note = qobject_cast<Note*>(note->databaseObject());
        Q_ASSERT(db_note);

        if (d->pointCount < db_note->pointCount()) {
            d->pointCount = db_note->pointCount();
            updateVBO();
        }
    }
}

void FCurveScene::removeNote(NoteScene *note)
{
    d->linkedNotes.removeOne(note);

    Note *db_note = qobject_cast<Note*>(note->databaseObject());
    Q_ASSERT(db_note);

    if (d->pointCount == db_note->pointCount())
        d->updatePointCount();
}

int FCurveScene::maxPointCount() const
{
    return d->pointCount;
}

void FCurveScene::setMaxPointCount(int count)
{
    if (d->pointCount < count) {
        d->pointCount = count;
        updateVBO();
    }
}

void FCurveScene::updateVBO()
{
}

void FCurveScene::updateProperty(int index)
{
    SceneObject::updateProperty(index);
}
