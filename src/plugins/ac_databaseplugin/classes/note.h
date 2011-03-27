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

#ifndef AC_NOTE_H
#define AC_NOTE_H

#include <databaseplugin/classes/object.h>

#include <ac_databaseplugin/ac_database_global.h>

namespace AudioCarver {
namespace Internal {

class NoteData;

} // namespace Internal

class AC_DATABASE_EXPORT Note : public Database::Object
{
    Q_OBJECT

    Q_PROPERTY(int pointCount READ pointCount WRITE setPointCount)
    Q_PROPERTY(Database::Object* pitchCurve READ pitchCurve WRITE setPitchCurve)

public:
    Note(QObject *parent = 0);
private:
    virtual ~Note();
    Q_DISABLE_COPY(Note)

public:
    int pointCount() const;
    void setPointCount(int count);

    Database::Object *pitchCurve() const;
    void setPitchCurve(Database::Object *curve);

private:
    Internal::NoteData *d;
};

} // namespace AudioCarver

#endif // AC_NOTE_H
