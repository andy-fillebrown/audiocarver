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
    MiList *notes;

    AcTuningData(AcTuning *q)
        :   MiLinkableObjectData(q)
        ,   centerNote(60.0f)
        ,   notes(new MiList(q, q->propertyIndex("notes")))
    {}

    ~AcTuningData()
    {
        delete notes;
    }
};

class AcTuningNoteData
{
public:
    qreal cents;
    QColor color;

    AcTuningNoteData(qreal cents)
        :   cents(cents)
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

MiList *AcTuning::notes() const
{
    return d->notes;
}

MiObject *AcTuning::createObject(const QString &className)
{
    if (className == "TuningNote") {
        AcTuningNote *note = new AcTuningNote(0.0f, this);
        d->notes->append(note);
        return note;
    }
    return 0;
}

AcTuningNote::AcTuningNote(qreal cents, QObject *parent)
    :   MiObject(parent)
    ,   d(new AcTuningNoteData(cents))
{}

AcTuningNote::~AcTuningNote()
{
    delete d;
}

qreal AcTuningNote::cents() const
{
    return d->cents;
}

void AcTuningNote::setCents(qreal cents)
{
    if (d->cents == cents)
        return;
    d->cents = cents;
    emit propertyChanged(propertyIndex("cents"));
}

const QColor &AcTuningNote::color() const
{
    return d->color;
}

void AcTuningNote::setColor(const QColor &color)
{
    if (d->color == color)
        return;
    d->color = color;
    emit propertyChanged(propertyIndex("color"));
}
