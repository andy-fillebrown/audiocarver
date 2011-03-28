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

#include "tuning.h"

#include <databaseplugin/classes/list.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class TuningData : public Database::Internal::LinkableObjectData
{
public:
    qreal centerNote;
    Database::List *tuningNotes;

    TuningData(Tuning *q)
        :   Database::Internal::LinkableObjectData(q)
        ,   centerNote(60.0f)
        ,   tuningNotes(new Database::List(q, q->propertyIndex("noteOffsets")))
    {}

    ~TuningData()
    {
        delete tuningNotes;
    }
};

class TuningNoteData
{
public:
    qreal note;

    TuningNoteData(qreal note)
        :   note(note)
    {}
};

} // namespace Internal
} // namespace AudioCarver

Tuning::Tuning(QObject *parent)
    :   Object(parent)
    ,   d(new TuningData(this))
{}

Tuning::~Tuning()
{
    delete d;
}

qreal Tuning::centerNote() const
{
    return d->centerNote;
}

void Tuning::setCenterNote(qreal centerNote)
{
    if (d->centerNote == centerNote)
        return;
    d->centerNote = centerNote;
    emit propertyChanged(propertyIndex("centerNote"));
}

Database::List *Tuning::tuningNotes() const
{
    return d->tuningNotes;
}

Database::Object *Tuning::createObject(const QString &className)
{
    if (className == "TuningNote") {
        TuningNote *tuningNote = new TuningNote(0.0f, this);
        d->tuningNotes->append(tuningNote);
        return tuningNote;
    }
    return 0;
}

TuningNote::TuningNote(qreal note, QObject *parent)
    :   Object(parent)
    ,   d(new TuningNoteData(note))
{}

TuningNote::~TuningNote()
{
    delete d;
}

qreal TuningNote::note() const
{
    return d->note;
}

void TuningNote::setNote(qreal note)
{
    if (d->note == note)
        return;
    d->note = note;
    emit propertyChanged(propertyIndex("note"));
}
