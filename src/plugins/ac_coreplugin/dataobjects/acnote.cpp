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

#include "acnote.h"

#include <actrack.h>

class NotePrivate : public ScoreObjectPrivate
{
public:
    qreal length;

    NotePrivate(Note *q)
        :   ScoreObjectPrivate(q)
        ,   length(0.0f)
    {}
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
    d->length = length;
}

Track *Note::parent() const
{
    return qobject_cast<Track*>(QObject::parent());
}

bool Note::setData(const QVariant &value, int role)
{
    switch (role) {
    case LengthRole:
        setLength(value.toReal());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}
