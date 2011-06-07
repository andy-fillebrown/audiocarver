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
    qreal length;

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
        ,   length(128.0f)
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
    }
};

} // namespace Private

static AcScore *instance = 0;

AcScore::AcScore(QObject *parent)
    :   MiRoot(parent)
    ,   d(new AcScoreData(this))
{
    ::instance = this;

    d->init();
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

qreal AcScore::length() const
{
    return d->length;
}

void AcScore::setLength(qreal length)
{
    if (length < 1.0f)
        length = 1.0f;
    if (d->length == length)
        return;
    d->length = length;
    emit propertyChanged(propertyIndex("length"));
}

AcGuideline *AcScore::createBarline()
{
    AcGuideline *barline = new AcGuideline(this);
    d->barlines->append(barline);
    return barline;
}

AcGuideline *AcScore::createTuning()
{
    AcGuideline *tuning = new AcGuideline(this);
    d->tunings->append(tuning);
    return tuning;
}

AcFCurve *AcScore::createCurve()
{
    AcFCurve *curve = new AcFCurve(this);
    d->curves->append(curve);
    return curve;
}

AcNote *AcScore::createNote()
{
    AcNote *note = new AcNote(this);
    d->notes->append(note);
    return note;
}

AcTrack *AcScore::createTrack()
{
    AcTrack *track = new AcTrack(this);
    d->tracks->append(track);
    return track;
}

AcGridSettings *AcScore::gridSettings() const
{
    return d->gridSettings;
}

AcViewSettings *AcScore::viewSettings() const
{
    return d->viewSettings;
}

AcGuideline *AcScore::barlineAt(int i)
{
    return qobject_cast<AcGuideline*>(d->barlines->at(i));
}

AcGuideline *AcScore::tuningAt(int i)
{
    return qobject_cast<AcGuideline*>(d->tunings->at(i));
}

AcFCurve *AcScore::curveAt(int i)
{
    return qobject_cast<AcFCurve*>(d->curves->at(i));
}

AcNote *AcScore::noteAt(int i)
{
    return qobject_cast<AcNote*>(d->notes->at(i));
}

AcTrack *AcScore::trackAt(int i)
{
    return qobject_cast<AcTrack*>(d->tracks->at(i));
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

QString &AcScore::normalizeClassName(QString &className) const
{
    // Remove "Ac" prefix.
    return className.remove(0, 2);
}

MiObject *AcScore::createObject(const QString &className)
{
    if (className == "Barline")
        return createBarline();
    if (className == "FCurve")
        return createCurve();
    if (className == "Note")
        return createNote();
    if (className == "Tuning")
        return createTuning();
    if (className == "Track")
        return createTrack();
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
