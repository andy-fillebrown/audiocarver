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

#include "ac_tuning.h"

#include <mi_list.h>

using namespace Private;

namespace Private {

class AcTuningData : public MiLinkableObjectData
{
public:
    qreal centerNote;
    MiList *tuningNotes;

    AcTuningData(AcTuning *q)
        :   MiLinkableObjectData(q)
        ,   centerNote(60.0f)
        ,   tuningNotes(new MiList(q, q->propertyIndex("noteOffsets")))
    {}

    ~AcTuningData()
    {
        delete tuningNotes;
    }
};

class AcTuningNoteData
{
public:
    qreal note;

    AcTuningNoteData(qreal note)
        :   note(note)
    {}
};

} // namespace Private

AcTuning::AcTuning(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcTuningData(this))
{}

AcTuning::~AcTuning()
{
    delete d;
}

qreal AcTuning::centerNote() const
{
    return d->centerNote;
}

void AcTuning::setCenterNote(qreal centerNote)
{
    if (d->centerNote == centerNote)
        return;
    d->centerNote = centerNote;
    emit propertyChanged(propertyIndex("centerNote"));
}

MiList *AcTuning::tuningNotes() const
{
    return d->tuningNotes;
}

MiObject *AcTuning::createObject(const QString &className)
{
    if (className == "TuningNote") {
        AcTuningNote *tuningNote = new AcTuningNote(0.0f, this);
        d->tuningNotes->append(tuningNote);
        return tuningNote;
    }
    return 0;
}

AcTuningNote::AcTuningNote(qreal note, QObject *parent)
    :   MiObject(parent)
    ,   d(new AcTuningNoteData(note))
{}

AcTuningNote::~AcTuningNote()
{
    delete d;
}

qreal AcTuningNote::note() const
{
    return d->note;
}

void AcTuningNote::setNote(qreal note)
{
    if (d->note == note)
        return;
    d->note = note;
    emit propertyChanged(propertyIndex("note"));
}
