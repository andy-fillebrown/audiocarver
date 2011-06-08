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

static bool guidelineLessThan(MiObject *a, MiObject *b)
{
    AcGuideline *aa = qobject_cast<AcGuideline*>(a);
    AcGuideline *bb = qobject_cast<AcGuideline*>(b);
    return aa->location() < bb->location();
}

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
    connect(this, SIGNAL(propertyChanged(int)), SLOT(updateScoreProperty(int)));
}

AcScore::~AcScore()
{
    delete d;
}

AcScore *AcScore::instance()
{
    return ::instance;
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

int AcScore::barlineCount() const
{
    return d->barlines->count();
}

int AcScore::tuningCount() const
{
    return d->tunings->count();
}

int AcScore::curveCount() const
{
    return d->curves->count();
}

int AcScore::noteCount() const
{
    return d->notes->count();
}

int AcScore::trackCount() const
{
    return d->tracks->count();
}

AcGuideline *AcScore::addBarline(AcGuideline *barline)
{
    if (barline)
        barline->setParent(this);
    else
        barline = new AcGuideline(this);
    d->barlines->append(barline);
    return barline;
}

AcGuideline *AcScore::addTuning(AcGuideline *tuning)
{
    if (tuning)
        tuning->setParent(this);
    else
        tuning = new AcGuideline(this);
    d->tunings->append(tuning);
    return tuning;
}

AcFCurve *AcScore::addCurve(AcFCurve *curve)
{
    if (curve)
        curve->setParent(this);
    else
        curve = new AcFCurve(this);
    d->curves->append(curve);
    return curve;
}

AcNote *AcScore::addNote(AcNote *note)
{
    if (note)
        note->setParent(note);
    else
        note = new AcNote(this);
    d->notes->append(note);
    return note;
}

AcTrack *AcScore::addTrack(AcTrack *track)
{
    if (track)
        track->setParent(this);
    else
        track = new AcTrack(this);
    d->tracks->append(track);
    return track;
}

void AcScore::addBarlines(const QList<MiObject*> &barlines)
{
    foreach (MiObject *object, barlines)
        object->setParent(this);
    d->barlines->append(barlines);
}

void AcScore::addTunings(const QList<MiObject*> &tunings)
{
    foreach (MiObject *object, tunings)
        object->setParent(this);
    d->tunings->append(tunings);
}

void AcScore::addCurves(const QList<MiObject*> &curves)
{
    foreach (MiObject *object, curves)
        object->setParent(this);
    d->curves->append(curves);
}

void AcScore::addNotes(const QList<MiObject*> &notes)
{
    foreach (MiObject *object, notes)
        object->setParent(this);
    d->notes->append(notes);
}

void AcScore::addTracks(const QList<MiObject*> &tracks)
{
    foreach (MiObject *object, tracks)
        object->setParent(this);
    d->tracks->append(tracks);
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

void AcScore::clearBarlines()
{
    d->barlines->deleteAll();
}

void AcScore::clearTunings()
{
    d->tunings->deleteAll();
}

void AcScore::clear()
{
    d->tracks->deleteAll();
    d->notes->deleteAll();
    d->curves->deleteAll();
    clearTunings();
    clearBarlines();
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
        return addBarline();
    if (className == "FCurve")
        return addCurve();
    if (className == "Note")
        return addNote();
    if (className == "Tuning")
        return addTuning();
    if (className == "Track")
        return addTrack();
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

void AcScore::updateScoreProperty(int propertyIndex)
{
    QString propName = propertyName(propertyIndex);
    if ("barlines" == propName) {
        for (int i = 0;  i < d->barlines->count();  ++i)
            connect(d->barlines->at(i), SIGNAL(propertyChanged(int)), SLOT(sortBarlines()), Qt::UniqueConnection);
        blockSignals(true);
        sortBarlines();
        blockSignals(false);
    }
    else if ("tunings" == propName) {
        for (int i = 0;  i < d->tunings->count();  ++i)
            connect(d->tunings->at(i), SIGNAL(propertyChanged(int)), SLOT(sortTunings()), Qt::UniqueConnection);
        blockSignals(true);
        sortTunings();
        blockSignals(false);
    }
}

void AcScore::sortBarlines()
{
    d->barlines->sort(guidelineLessThan);
}

void AcScore::sortTunings()
{
    d->tunings->sort(guidelineLessThan);
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
