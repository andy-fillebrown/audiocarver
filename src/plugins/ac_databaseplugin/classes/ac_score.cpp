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
#include <ac_guideline.h>
#include <ac_note.h>
#include <ac_track.h>
#include <ac_viewsettings.h>

#include <mi_list.h>

using namespace Private;

namespace Private {

class AcScoreData
{
public:
    AcScore *q;
    MiList *settings;
    MiList *barlines;
    MiList *tunings;
    MiList *curves;
    MiList *notes;
    MiList *tracks;

    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScoreData(AcScore *q)
        :   q(q)
        ,   settings(new MiConstantList(q, q->propertyIndex("settings")))
        ,   barlines(new MiList(q, q->propertyIndex("barlines")))
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
        delete barlines;
        delete settings;
    }

    void init()
    {
        gridSettings = new AcGridSettings(q);
        viewSettings = new AcViewSettings(q);
        settings->append(gridSettings);
        settings->append(viewSettings);

        q->createObject("Barline");
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

MiList *AcScore::barlines() const
{
    return d->barlines;
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

AcGridSettings *AcScore::gridSettings() const
{
    return d->gridSettings;
}

AcViewSettings *AcScore::viewSettings() const
{
    return d->viewSettings;
}

void AcScore::clear()
{
    d->tracks->deleteAll();
    d->notes->deleteAll();
    d->curves->deleteAll();
    d->tunings->deleteAll();
    d->barlines->deleteAll();
    d->settings->deleteAll();

    d->init();
}

/*!
  \todo Implement.
  */
qreal AcScore::length() const
{
    return 128.0f;
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
    if (className == "Barline") {
        AcGuideline *guideline = new AcGuideline(this);
        d->barlines->append(guideline);
        return guideline;
    }
    if (className == "Note") {
        AcNote *note = new AcNote(this);
        d->notes->append(note);
        return note;
    }
    if (className == "Tuning") {
        AcGuideline *guideline = new AcGuideline(this);
        d->tunings->append(guideline);
        return guideline;
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
