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
#include <ac_barline.h>
#include <ac_fcurve.h>
#include <ac_gridsettings.h>
#include <ac_note.h>
#include <ac_track.h>
#include <ac_tuningline.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <mi_list.h>
#include <mi_scopedsignalblocker.h>

using namespace Private;

namespace Private {

class AcScoreData
{
public:
    AcScore *q;

    qreal length;
    MiConstantObjectList settings;
    MiList<AcBarLine> barLines;
    MiList<AcTuningLine> tuningLines;
    MiList<AcFCurve> curves;
    MiList<AcNote> notes;
    MiList<AcTrack> tracks;

    MiFont *fontSettings;
    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScoreData(AcScore *q)
        :   q(q)
        ,   length(128.0f)
        ,   settings("settings", q)
        ,   barLines("barLines", q)
        ,   tuningLines("tuningLines", q)
        ,   curves("curves", q)
        ,   notes("notes", q)
        ,   tracks("tracks", q)
        ,   fontSettings(0)
        ,   gridSettings(0)
        ,   viewSettings(0)
    {}

    void init()
    {
        fontSettings = new MiFont(q);
        gridSettings = new AcGridSettings(q);
        viewSettings = new AcViewSettings(q);
        settings.append(fontSettings);
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

MiList<AcBarLine> &AcScore::barLines() const
{
    return d->barLines;
}

MiList<AcTuningLine> &AcScore::tuningLines() const
{
    return d->tuningLines;
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

MiFont *AcScore::fontSettings() const
{
    return d->fontSettings;
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
    d->tracks.clear();
    d->notes.clear();
    d->curves.clear();
    d->tuningLines.clear();
    d->barLines.clear();
    d->settings.clear();
    d->init();
}

QString &AcScore::normalizeClassName(QString &className) const
{
    // Remove "Ac" prefix.
    return className.remove(0, 2);
}

MiObject *AcScore::createObject(const QString &className)
{
    if (className == "BarLine")
        return d->barLines.add();
    if (className == "FCurve")
        return d->curves.add();
    if (className == "Note")
        return d->notes.add();
    if (className == "TuningLine")
        return d->tuningLines.add();
    if (className == "Track")
        return d->tracks.add();
    return 0;
}

MiObject *AcScore::findObject(const QString &className) const
{
    if (className == "Font")
        return d->fontSettings;
    if (className == "GridSettings")
        return d->gridSettings;
    if (className == "ViewSettings")
        return d->viewSettings;
    return 0;
}

void AcScore::updateScoreProperty(const QString &propertyName)
{
    if ("barLines" == propertyName) {
        for (int i = 0;  i < d->barLines.count();  ++i)
            connect(d->barLines.at(i), SIGNAL(propertyChanged(QString)), SLOT(updateBarLineProperty(QString)), Qt::UniqueConnection);
        sortBarLines();
    }
    else if ("tuningLines" == propertyName) {
        for (int i = 0;  i < d->tuningLines.count();  ++i)
            connect(d->tuningLines.at(i), SIGNAL(propertyChanged(QString)), SLOT(updateTuningLineProperty(QString)), Qt::UniqueConnection);
        sortTuningLines();
    }
}

void AcScore::updateBarLineProperty(const QString &propertyName)
{
    if ("location" == propertyName)
        sortBarLines();
}

void AcScore::updateTuningLineProperty(const QString &propertyName)
{
    if ("location" == propertyName)
        sortTuningLines();
}

void AcScore::sortBarLines()
{
    MiScopedSignalBlocker blockSignals(this);
    d->barLines.sort();
}

void AcScore::sortTuningLines()
{
    MiScopedSignalBlocker blockSignals(this);
    d->tuningLines.sort();
}

MiObjectList *AcScore::settingsObjects() const
{
    return &(d->settings);
}

MiObjectList *AcScore::barLineObjects() const
{
    return d->barLines.objects();
}

MiObjectList *AcScore::tuningLineObjects() const
{
    return d->tuningLines.objects();
}

MiObjectList *AcScore::curveObjects() const
{
    return d->curves.objects();
}

MiObjectList *AcScore::noteObjects() const
{
    return d->notes.objects();
}

MiObjectList *AcScore::trackObjects() const
{
    return d->tracks.objects();
}
