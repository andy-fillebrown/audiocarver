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

#include <mi_objectlist.h>

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

    qreal length;
    MiConstantObjectList settings;
    MiList<AcGuideline> barlines;
    MiList<AcGuideline> tunings;
    MiList<AcFCurve> curves;
    MiList<AcNote> notes;
    MiList<AcTrack> tracks;

    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScoreData(AcScore *q)
        :   q(q)
        ,   length(128.0f)
        ,   settings("settings", q)
        ,   barlines("barlines", q)
        ,   tunings("tunings", q)
        ,   curves("curves", q)
        ,   notes("notes", q)
        ,   tracks("tracks", q)
        ,   gridSettings(0)
        ,   viewSettings(0)
    {}

    void init()
    {
        gridSettings = new AcGridSettings(q);
        viewSettings = new AcViewSettings(q);
        settings.append(gridSettings);
        settings.append(viewSettings);
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
    connect(this, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
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
    emit propertyChanged("length");
}

MiList<AcGuideline> &AcScore::barlines() const
{
    return d->barlines;
}

MiList<AcGuideline> &AcScore::tunings() const
{
    return d->tunings;
}

MiList<AcFCurve> &AcScore::curves() const
{
    return d->curves;
}

MiList<AcNote> &AcScore::notes() const
{
    return d->notes;
}

MiList<AcTrack> &AcScore::tracks() const
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
    d->tracks.deleteAll();
    d->notes.deleteAll();
    d->curves.deleteAll();
    d->tunings.deleteAll();
    d->barlines.deleteAll();
    d->settings.deleteAll();
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
        return d->barlines.add();
    if (className == "FCurve")
        return d->curves.add();
    if (className == "Note")
        return d->notes.add();
    if (className == "Tuning")
        return d->tunings.add();
    if (className == "Track")
        return d->tracks.add();
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

void AcScore::updateScoreProperty(const QString &propertyName)
{
    if ("barlines" == propertyName) {
        for (int i = 0;  i < d->barlines.count();  ++i)
            connect(d->barlines.at(i), SIGNAL(propertyChanged(QString)), SLOT(updateBarlineProperty(QString)), Qt::UniqueConnection);
        sortBarlines();
    }
    else if ("tunings" == propertyName) {
        for (int i = 0;  i < d->tunings.count();  ++i)
            connect(d->tunings.at(i), SIGNAL(propertyChanged(QString)), SLOT(updateTuningProperty(QString)), Qt::UniqueConnection);
        sortTunings();
    }
}

void AcScore::updateBarlineProperty(const QString &propertyName)
{
    if ("location" == propertyName)
        sortBarlines();
}

void AcScore::updateTuningProperty(const QString &propertyName)
{
    if ("location" == propertyName)
        sortTunings();
}

void AcScore::sortBarlines()
{
    blockSignals(true);
    d->barlines.sort(guidelineLessThan);
    blockSignals(false);
}

void AcScore::sortTunings()
{
    blockSignals(true);
    d->tunings.sort(guidelineLessThan);
    blockSignals(false);
}

MiObjectList *AcScore::settingObjectList() const
{
    return &(d->settings);
}

MiObjectList *AcScore::barlineObjectList() const
{
    return d->barlines.objects();
}

MiObjectList *AcScore::tuningObjectList() const
{
    return d->tunings.objects();
}

MiObjectList *AcScore::curveObjectList() const
{
    return d->curves.objects();
}

MiObjectList *AcScore::noteObjectList() const
{
    return d->notes.objects();
}

MiObjectList *AcScore::trackObjectList() const
{
    return d->tracks.objects();
}
