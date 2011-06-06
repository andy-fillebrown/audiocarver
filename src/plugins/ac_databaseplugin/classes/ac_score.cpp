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

#include "ac_score.h"

#include <ac_fcurve.h>
#include <ac_gridsettings.h>
#include <ac_meter.h>
#include <ac_note.h>
#include <ac_tempo.h>
#include <ac_track.h>
#include <ac_tuning.h>
#include <ac_viewsettings.h>

#include <mi_list.h>

using namespace Private;

namespace Private {

class AcScoreData
{
public:
    AcScore *q;
    MiList *settings;
    MiList *meters;
    MiList *tempos;
    MiList *tunings;
    MiList *curves;
    MiList *notes;
    MiList *tracks;

    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScoreData(AcScore *q)
        :   q(q)
        ,   settings(new MiConstantList(q, q->propertyIndex("settings")))
        ,   meters(new MiList(q, q->propertyIndex("meters")))
        ,   tempos(new MiList(q, q->propertyIndex("tempos")))
        ,   tunings(new MiList(q, q->propertyIndex("tunings")))
        ,   curves(new MiList(q, q->propertyIndex("curves")))
        ,   notes(new MiList(q, q->propertyIndex("notes")))
        ,   tracks(new MiList(q, q->propertyIndex("tracks")))
        ,   gridSettings(0)
        ,   viewSettings(0)
    {}

    ~AcScoreData()
    {
        delete tracks;
        delete notes;
        delete curves;
        delete tunings;
        delete tempos;
        delete meters;
        delete settings;
    }

    void init()
    {
        gridSettings = new AcGridSettings(q);
        viewSettings = new AcViewSettings(q);
        settings->append(gridSettings);
        settings->append(viewSettings);

        q->createObject("Meter");
        q->createObject("Tempo");
        q->createObject("Tuning");
    }
};

} // namespace Private

static AcScore *instance = 0;

AcScore::AcScore(QObject *parent)
    :   MiRoot(parent)
    ,   d(new AcScoreData(this))
{
    d->init();
    ::instance = this;
}

AcScore::~AcScore()
{
    delete d;
}

AcScore *AcScore::instance()
{
    return ::instance;
}

MiList *AcScore::settings() const
{
    return d->settings;
}

MiList *AcScore::meters() const
{
    return d->meters;
}

MiList *AcScore::tempos() const
{
    return d->tempos;
}

MiList *AcScore::tunings() const
{
    return d->tunings;
}

MiList *AcScore::curves() const
{
    return d->curves;
}

MiList *AcScore::notes() const
{
    return d->notes;
}

MiList *AcScore::tracks() const
{
    return d->tracks;
}

void AcScore::clear()
{
    d->tracks->deleteAll();
    d->notes->deleteAll();
    d->curves->deleteAll();
    d->tunings->deleteAll();
    d->tempos->deleteAll();
    d->meters->deleteAll();
    d->settings->deleteAll();

    d->init();
}

QString &AcScore::normalizeClassName(QString &className) const
{
    // Remove "Ac" prefix.
    return className.remove(0, 2);
}

MiObject *AcScore::createObject(const QString &className)
{
    if (className == "FCurve") {
        AcFCurve *fcurve = new AcFCurve(this);
        d->curves->append(fcurve);
        return fcurve;
    }
    if (className == "Meter") {
        AcMeter *meter = new AcMeter(this);
        d->meters->append(meter);
        return meter;
    }
    if (className == "Note") {
        AcNote *note = new AcNote(this);
        d->notes->append(note);
        return note;
    }
    if (className == "Tempo") {
        AcTempo *tempo = new AcTempo(this);
        d->tempos->append(tempo);
        return tempo;
    }
    if (className == "Tuning") {
        AcTuning *tuning = new AcTuning(this);
        d->tunings->append(tuning);
        return tuning;
    }
    if (className == "Track") {
        AcTrack *track = new AcTrack(this);
        d->tracks->append(track);
        return track;
    }
    return 0;
}

MiObject *AcScore::findObject(const QString &className) const
{
    if (className == "GridSettings")
        return d->gridSettings;
    if (className == "ViewSettings")
        return d->viewSettings;
    return 0;
}
