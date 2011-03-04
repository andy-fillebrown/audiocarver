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

#include "notescene.h"

#include "fcurvescene.h"
#include "trackscene.h"

#include <ac_databaseplugin/classes/note.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class NoteScenePrivate
{
public:
    NoteScene *q;
    Note *note;
    TrackScene *track;
    FCurveScene *pitchCurve;
    FCurveScene *volumeCurve;
    int lineIBOId;
    int polygonIBOId;

    NoteScenePrivate(NoteScene *q)
        :   q(q)
        ,   note(qobject_cast<Note*>(q->databaseObject()))
        ,   track(qobject_cast<TrackScene*>(q->parent()))
        ,   pitchCurve(track->parent()->findChild<FCurveScene*>(note->pitchCurve()->id()))
        ,   volumeCurve(track->parent()->findChild<FCurveScene*>(note->volumeCurve()->id()))
    {
        Q_ASSERT(note);
        Q_ASSERT(track);

        if (pitchCurve)
            pitchCurve->appendNote(q);

        if (volumeCurve)
            volumeCurve->appendNote(q);
    }

    ~NoteScenePrivate()
    {
        volumeCurve = 0;
        pitchCurve = 0;
        track = 0;
        note = 0;
        q = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

NoteScene::NoteScene(Database::Object *databaseObject, QObject *parent)
    :   SceneObject(databaseObject, parent)
{
}

NoteScene::~NoteScene()
{
}

void NoteScene::updateIBO()
{
}

void NoteScene::updateProperty(int index)
{
    const QString propertyName = databaseObject()->propertyName(index);

    if (propertyName == "pointCount") {
        const int pointCount = d->note->pointCount();
        d->pitchCurve->setMaxPointCount(pointCount);
        d->volumeCurve->setMaxPointCount(pointCount);
        return;
    }

    if (propertyName == "pitchCurve") {
        if (d->pitchCurve)
            d->pitchCurve->removeNote(this);
        d->pitchCurve = d->track->parent()->findChild<FCurveScene*>(d->note->pitchCurve()->id());
        if (d->pitchCurve)
            d->pitchCurve->appendNote(this);
        return;
    }

    if (propertyName == "volumeCurve") {
        if (d->volumeCurve)
            d->volumeCurve->removeNote(this);
        d->volumeCurve = d->track->parent()->findChild<FCurveScene*>(d->note->volumeCurve()->id());
        if (d->volumeCurve)
            d->volumeCurve->appendNote(this);
        return;
    }

    SceneObject::updateProperty(index);
}
