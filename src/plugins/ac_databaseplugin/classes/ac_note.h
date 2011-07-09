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

class AcPitchPoint;
class AcVolumePoint;
template <typename T> class MiList;

namespace Private {

class AcNoteData;

} // namespace Private

class AC_DATABASE_EXPORT AcNote : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(MiObjectList* pitchPoints READ pitchPointObjects)
    Q_PROPERTY(MiObjectList* volumePoints READ volumePointObjects)

public:
    AcNote(QObject *parent = 0);
    virtual ~AcNote();

    MiList<AcPitchPoint> &pitchPoints() const;
    MiList<AcVolumePoint> &volumePoints() const;

protected:
    virtual MiObject *createObject(const QString &className);

private:
    Q_DISABLE_COPY(AcNote)
    Private::AcNoteData *d;

    MiObjectList *pitchPointObjects() const;
    MiObjectList *volumePointObjects() const;
};

#endif // AC_NOTE_H
