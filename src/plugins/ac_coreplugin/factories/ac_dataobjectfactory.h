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

#ifndef AC_DATAOBJECTFACTORY_H
#define AC_DATAOBJECTFACTORY_H

#include <ac_core_global.h>
#include <ac_controlline.h>
#include <ac_gridsettings.h>
#include <ac_pitchline.h>
#include <ac_timeline.h>
#include <ac_track.h>
#include <ac_viewsettings.h>
#include <mi_dataobjectfactory.h>

class AC_CORE_EXPORT AcDataObjectFactory : public MiDataObjectFactory
{
    Q_OBJECT
    Q_DISABLE_COPY(AcDataObjectFactory)

public:
    explicit AcDataObjectFactory(QObject *parent = 0)
        :   MiDataObjectFactory(parent)
    {}

    ~AcDataObjectFactory()
    {}

protected:
    virtual QObject *createObject(const QString &className, QObject *parent)
    {
        if ("AcPitchPoint" == className)
            return createPitchPoint(parent);
        if ("AcNote" == className)
            return createNote(parent);
        if ("AcTrack" == className)
            return createTrack(parent);
        return MiDataObjectFactory::createObject(className, parent);
    }

    virtual AcPitchPoint *createPitchPoint(QObject *parent)
    {
        AcPitchPoint *pitchPoint = new AcPitchPoint(parent);
        addPropertyBagTo(pitchPoint);
        return pitchPoint;
    }

    virtual AcControlPoint *createControlPoint(QObject *parent)
    {
        AcControlPoint *controlPoint = new AcControlPoint(parent);
        addPropertyBagTo(controlPoint);
        return controlPoint;
    }

    virtual AcNote *createNote(QObject *parent)
    {
        AcNote *note = new AcNote(parent);
        addPropertyBagTo(note);
        return note;
    }

    virtual AcTrack *createTrack(QObject *parent)
    {
        AcTrack *track = new AcTrack(parent);
        addPropertyBagTo(track);
        return track;
    }

    virtual MiObjectList *createList(const QString &listObjectClassName, QObject *parent)
    {
        if ("AcPitchPoint" == listObjectClassName)
            return new AcPitchCurve(parent);
        return MiDataObjectFactory::createList(listObjectClassName, parent);
    }
};

#endif // MI_DATAOBJECTFACTORY_H
