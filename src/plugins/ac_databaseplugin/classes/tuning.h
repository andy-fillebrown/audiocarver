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

#include <databaseplugin/classes/object.h>

#include <ac_databaseplugin/ac_database_global.h>

namespace AudioCarver {
namespace Internal {

class TuningData;
class TuningNoteData;

} // namespace Internal

class AC_DATABASE_EXPORT Tuning : public Database::Object
{
    Q_OBJECT

    Q_PROPERTY(qreal centerNote READ centerNote WRITE setCenterNote)
    Q_PROPERTY(Database::List* tuningNotes READ tuningNotes)

public:
    Tuning(QObject *parent = 0);
private:
    virtual ~Tuning();
    Q_DISABLE_COPY(Tuning)

public:
    qreal centerNote() const;
    void setCenterNote(qreal centerNote);

    Database::List *tuningNotes() const;

    Database::Object *createObject(const QString &className);

private:
    Internal::TuningData *d;
};

class AC_DATABASE_EXPORT TuningNote : public Database::Object
{
    Q_OBJECT

    Q_PROPERTY(qreal note READ note WRITE setNote)

public:
    TuningNote(qreal note = 0.0f, QObject *parent = 0);
private:
    virtual ~TuningNote();
    Q_DISABLE_COPY(TuningNote)

public:
    qreal note() const;
    void setNote(qreal note);

private:
    Internal::TuningNoteData *d;
};

} // namespace AudioCarver

#endif // AC_TUNING_H
