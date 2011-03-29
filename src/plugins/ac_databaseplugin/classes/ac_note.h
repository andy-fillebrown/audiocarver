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

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcNoteData;

} // namespace Private

class AC_DATABASE_EXPORT AcNote : public MiObject
{
    Q_OBJECT

    Q_PROPERTY(int pointCount READ pointCount WRITE setPointCount)
    Q_PROPERTY(MiObject* pitchCurve READ pitchCurve WRITE setPitchCurve)

public:
    AcNote(QObject *parent = 0);
private:
    virtual ~AcNote();
    Q_DISABLE_COPY(AcNote)

public:
    int pointCount() const;
    void setPointCount(int count);

    MiObject *pitchCurve() const;
    void setPitchCurve(MiObject *curve);

private:
    Private::AcNoteData *d;
};

#endif // AC_NOTE_H
