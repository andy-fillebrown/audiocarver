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

class AcFCurve;

namespace Private {

class AcNoteData;

} // namespace Private

class AC_DATABASE_EXPORT AcNote : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal startTime READ startTime WRITE setStartTime)
    Q_PROPERTY(qreal duration READ duration WRITE setDuration)
    Q_PROPERTY(qreal pitchScale READ pitchScale WRITE setPitchScale)
    Q_PROPERTY(qreal volumeScale READ volumeScale WRITE setVolumeScale)
    Q_PROPERTY(MiObject* pitchCurve READ pitchCurveObject WRITE setPitchCurveObject)
    Q_PROPERTY(MiObject* volumeCurve READ volumeCurveObject WRITE setVolumeCurveObject)
    Q_PROPERTY(int pitchPointCount READ pitchPointCount WRITE setPitchPointCount)
    Q_PROPERTY(int volumePointCount READ volumePointCount WRITE setVolumePointCount)

public:
    AcNote(QObject *parent = 0);
    virtual ~AcNote();

    qreal startTime() const;
    void setStartTime(qreal time);

    qreal duration() const;
    void setDuration(qreal duration);

    qreal pitchScale() const;
    void setPitchScale(qreal scale);

    qreal volumeScale() const;
    void setVolumeScale(qreal scale);

    int pitchPointCount() const;
    void setPitchPointCount(int count);

    int volumePointCount() const;
    void setVolumePointCount(int count);

    AcFCurve *pitchCurve() const;
    void setPitchCurve(AcFCurve *curve);

    AcFCurve *volumeCurve() const;
    void setVolumeCurve(AcFCurve *curve);

private:
    MiObject *pitchCurveObject() const;
    void setPitchCurveObject(MiObject *curve);

    MiObject *volumeCurveObject() const;
    void setVolumeCurveObject(MiObject *curve);

private:
    Q_DISABLE_COPY(AcNote)
    Private::AcNoteData *d;
};

#endif // AC_NOTE_H
