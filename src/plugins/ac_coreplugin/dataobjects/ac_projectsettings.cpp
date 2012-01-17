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

#include "ac_projectsettings.h"

#include <ac_score.h>

#include <QVariant>

ProjectSettings::ProjectSettings(QObject *parent)
    :   Object(*(new ProjectSettingsPrivate(this)), parent)
{
    setName("Project Settings");
}

const QString &ProjectSettings::outputDirectory() const
{
    Q_D(const ProjectSettings);
    return d->outputDirectory;
}

void ProjectSettings::setOutputDirectory(const QString &directory)
{
    Q_D(ProjectSettings);
    if (d->outputDirectory == directory)
        return;
    d->beginChangeData();
    d->outputDirectory = directory;
    d->endChangeData();
}

QString ProjectSettings::instrumentDirectory() const
{
    Q_D(const ProjectSettings);
    return d->instrumentDirectory;
}

void ProjectSettings::setInstrumentDirectory(const QString &directory)
{
    Q_D(ProjectSettings);
    if (d->instrumentDirectory == directory)
        return;
    d->beginChangeData();
    d->instrumentDirectory = directory;
    d->endChangeData();
}

const QString &ProjectSettings::audioFileType() const
{
    Q_D(const ProjectSettings);
    return d->audioFileType;
}

void ProjectSettings::setAudioFileType(const QString &fileType)
{
    Q_D(ProjectSettings);
    if (d->audioFileType == fileType)
        return;
    d->beginChangeData();
    d->audioFileType = fileType;
    d->endChangeData();
}

int ProjectSettings::sampleRate() const
{
    Q_D(const ProjectSettings);
    return d->sampleRate;
}

void ProjectSettings::setSampleRate(int rate)
{
    Q_D(ProjectSettings);
    if (d->sampleRate == rate)
        return;
    d->beginChangeData();
    d->sampleRate = rate;
    d->endChangeData();
}

int ProjectSettings::controlRate() const
{
    Q_D(const ProjectSettings);
    return d->controlRate;
}

void ProjectSettings::setControlRate(int rate)
{
    Q_D(ProjectSettings);
    if (d->controlRate == rate)
        return;
    d->beginChangeData();
    d->controlRate = rate;
    d->endChangeData();
}

int ProjectSettings::curveRate() const
{
    Q_D(const ProjectSettings);
    return d->curveRate;
}

void ProjectSettings::setCurveRate(int rate)
{
    Q_D(ProjectSettings);
    if (d->curveRate == rate)
        return;
    d->beginChangeData();
    d->curveRate = rate;
    d->endChangeData();
}

Score *ProjectSettings::score() const
{
    return object_cast<Score>(QObject::parent());
}

void ProjectSettings::clear()
{
    Q_D(ProjectSettings);
    d->clear();
}

QVariant ProjectSettings::data(int role) const
{
    switch (role) {
    case Ac::OutputDirectoryRole:
        return outputDirectory();
    case Ac::InstrumentDirectoryRole:
        return instrumentDirectory();
    case Ac::AudioFileTypeRole:
        return audioFileType();
    case Ac::SampleRateRole:
        return sampleRate();
    case Ac::ControlRateRole:
        return controlRate();
    case Ac::CurveRateRole:
        return curveRate();
    default:
        return Object::data(role);
    }
}

bool ProjectSettings::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::OutputDirectoryRole:
        setOutputDirectory(value.toString());
        return true;
    case Ac::InstrumentDirectoryRole:
        setInstrumentDirectory(value.toString());
        return true;
    case Ac::AudioFileTypeRole:
        setAudioFileType(value.toString());
        return true;
    case Ac::SampleRateRole:
        setSampleRate(value.toInt());
        return true;
    case Ac::ControlRateRole:
        setControlRate(value.toInt());
        return true;
    case Ac::CurveRateRole:
        setCurveRate(value.toInt());
        return true;
    default:
        return Object::setData(value, role);
    }
}
