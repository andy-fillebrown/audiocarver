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

#ifndef AC_TUNING_H
#define AC_TUNING_H

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcTuningData;
class AcTuningNoteData;

} // namespace Internal

class AC_DATABASE_EXPORT AcTuning : public MiObject
{
    Q_OBJECT

    Q_PROPERTY(qreal centerNote READ centerNote WRITE setCenterNote)
    Q_PROPERTY(MiList* tuningNotes READ tuningNotes)

public:
    AcTuning(QObject *parent = 0);
private:
    virtual ~AcTuning();
    Q_DISABLE_COPY(AcTuning)

public:
    qreal centerNote() const;
    void setCenterNote(qreal centerNote);

    MiList *tuningNotes() const;

    MiObject *createObject(const QString &className);

private:
    Private::AcTuningData *d;
};

class AC_DATABASE_EXPORT AcTuningNote : public MiObject
{
    Q_OBJECT

    Q_PROPERTY(qreal note READ note WRITE setNote)

public:
    AcTuningNote(qreal note = 0.0f, QObject *parent = 0);
private:
    virtual ~AcTuningNote();
    Q_DISABLE_COPY(AcTuningNote)

public:
    qreal note() const;
    void setNote(qreal note);

private:
    Private::AcTuningNoteData *d;
};

#endif // AC_TUNING_H
