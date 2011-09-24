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

#include <ac_graphicsitem.h>
#include <ac_track.h>

class NotePrivate : public ScoreObjectPrivate
{
public:
    qreal length;

    NotePrivate(Note *q)
        :   ScoreObjectPrivate(q)
        ,   length(0.0f)
    {}

    void init()
    {
        mainGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
        mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
        ScoreObjectPrivate::init();
    }
};

Note::Note(QObject *parent)
    :   ScoreObject(*(new NotePrivate(this)), parent)
{
    Q_D(Note);
    d->init();
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
