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

#include "ac_note.h"

#include <ac_controlcurve.h>
#include <ac_graphicsitem.h>
#include <ac_pitchcurve.h>
#include <ac_track.h>

class NotePrivate : public ScoreObjectPrivate
{
    Q_DECLARE_PUBLIC(Note)

public:
    qreal length;

    NotePrivate(Note *q)
        :   ScoreObjectPrivate(q)
        ,   length(0.0f)
    {
        mainGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
        mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
    }

    GraphicsParentPrivate *graphicsParent() const
    {
        Q_Q(const Note);
        Track *track = q->track();
        return track ? track->d_func() : 0;
    }
};

Note::Note(QObject *parent)
    :   ScoreObject(*(new NotePrivate(this)), parent)
{
    setObjectName("Note");
}

qreal Note::length() const
{
    Q_D(const Note);
    return d->length;
}

void Note::setLength(qreal length)
{
    Q_D(Note);
    if (d->length == length)
        return;
    d->beginChangeData();
    d->length = length;
    d->endChangeData();
}

Track *Note::track() const
{
    QObject *parent = QObject::parent();
    return parent ? qobject_cast<Track*>(parent->parent()) : 0;
}

PointList Note::points() const
{
    return PointList();
}

void Note::setPoints(const PointList &points, Ac::DragState dragState)
{
    Q_UNUSED(points);
    Q_UNUSED(dragState);
}

void Note::highlight()
{
    Q_D(Note);
    d->pitchCurve->highlight();
    int n = d->controlCurves->count();
    for (int i = 0;  i < n;  ++i)
        d->controlCurves->at(i)->highlight();
}

void Note::unhighlight()
{
    Q_D(Note);
    d->pitchCurve->unhighlight();
    int n = d->controlCurves->count();
    for (int i = 0;  i < n;  ++i)
        d->controlCurves->at(i)->unhighlight();
}

bool Note::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::LengthRole:
        setLength(value.toReal());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}
