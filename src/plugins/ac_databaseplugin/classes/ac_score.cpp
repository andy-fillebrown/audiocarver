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
#include <ac_gridsettings.h>
#include <ac_track.h>
#include <ac_tuningline.h>
#include <ac_valueline.h>
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
    MiList<AcTrack> tracks;
    MiList<AcBarLine> barLines;
    MiList<AcTuningLine> tuningLines;
    MiList<AcValueLine> valueLines;
    MiFont *fontSettings;
    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScoreData(AcScore *q)
        :   q(q)
        ,   length(128.0f)
        ,   settings("settings", q)
        ,   tracks("tracks", q)
        ,   barLines("barLines", q)
        ,   tuningLines("tuningLines", q)
        ,   valueLines("valueLines", q)
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

MiList<AcTrack> &AcScore::tracks() const
{
    return d->tracks;
}

MiList<AcBarLine> &AcScore::barLines() const
{
    return d->barLines;
}

MiList<AcTuningLine> &AcScore::tuningLines() const
{
    return d->tuningLines;
}

MiList<AcValueLine> &AcScore::valueLines() const
{
    return d->valueLines;
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
    d->valueLines.clear();
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
    if ("BarLine" == className)
        return d->barLines.add();
    if ("TuningLine" == className)
        return d->tuningLines.add();
    if ("ValueLine" == className)
        return d->valueLines.add();
    if ("Track" == className)
        return d->tracks.add();
    return 0;
}

MiObject *AcScore::findObject(const QString &className) const
{
    if ("Font" == className)
        return d->fontSettings;
    if ("GridSettings" == className)
        return d->gridSettings;
    if ("ViewSettings" == className)
        return d->viewSettings;
    return 0;
}

void AcScore::updateScoreProperty(const QString &propertyName)
{
    if ("barLines" == propertyName) {
        foreach (AcBarLine *barLine, d->barLines.list())
            connect(barLine, SIGNAL(propertyChanged(QString)), SLOT(updateBarLineProperty(QString)), Qt::UniqueConnection);
        sortBarLines();
    } else if ("tuningLines" == propertyName) {
        foreach (AcTuningLine *tuningLine, d->tuningLines.list())
            connect(tuningLine, SIGNAL(propertyChanged(QString)), SLOT(updateTuningLineProperty(QString)), Qt::UniqueConnection);
        sortTuningLines();
    } else if ("valueLines" == propertyName) {
        foreach (AcValueLine *valueLine, d->valueLines.list())
            connect(valueLine, SIGNAL(propertyChanged(QString)), SLOT(updateValueLineProperty(QString)), Qt::UniqueConnection);
        sortValueLines();
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

void AcScore::updateValueLineProperty(const QString &propertyName)
{
    if ("location" == propertyName)
        sortValueLines();
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

void AcScore::sortValueLines()
{
    MiScopedSignalBlocker blockSignals(this);
    d->valueLines.sort();
}

MiObjectList *AcScore::settingsObjects() const
{
    return &(d->settings);
}

MiObjectList *AcScore::trackObjects() const
{
    return d->tracks.objects();
}

MiObjectList *AcScore::barLineObjects() const
{
    return d->barLines.objects();
}

MiObjectList *AcScore::tuningLineObjects() const
{
    return d->tuningLines.objects();
}

MiObjectList *AcScore::valueLineObjects() const
{
    return d->valueLines.objects();
}
