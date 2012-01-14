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

#ifndef AC_PROJECTSETTINGS_H
#define AC_PROJECTSETTINGS_H

#include <ac_coreconstants.h>
#include <ac_namespace.h>

#include <mi_object.h>

class Score;

class ProjectSettingsPrivate;
class ProjectSettings : public Object
{
    Q_OBJECT
    Q_PROPERTY(QString outputDirectory READ outputDirectory WRITE setOutputDirectory)
    Q_PROPERTY(QString instrumentDirectory READ instrumentDirectory WRITE setInstrumentDirectory)
    Q_PROPERTY(QString audioFileType READ audioFileType WRITE setAudioFileType)
    Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate)
    Q_PROPERTY(int controlRate READ controlRate WRITE setControlRate)

public:
    enum { Type = Ac::ProjectSettingsItem };

    ProjectSettings(QObject *parent = 0);

    Score *score() const;

    void clear();

    // Properties
    const QString &outputDirectory() const;
    void setOutputDirectory(const QString &directory);
    QString instrumentDirectory() const;
    void setInstrumentDirectory(const QString &directory);
    const QString &audioFileType() const;
    void setAudioFileType(const QString &fileType);
    int sampleRate() const;
    void setSampleRate(int rate);
    int controlRate() const;
    void setControlRate(int rate);

    // IModelItem
    int type() const { return Type; }

    int persistentRoleAt(int i) const
    {
        switch (i - staticMetaObject.propertyOffset()) {
        case 0:
            return Ac::OutputDirectoryRole;
        case 1:
            return Ac::InstrumentDirectoryRole;
        case 2:
            return Ac::AudioFileTypeRole;
        case 3:
            return Ac::SampleRateRole;
        case 4:
            return Ac::ControlRateRole;
        default:
            return Object::persistentRoleAt(i);
        }
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DECLARE_PRIVATE(ProjectSettings)
};

class ProjectSettingsPrivate : public ObjectPrivate
{
    Q_DECLARE_PUBLIC(ProjectSettings)

public:
    QString outputDirectory;
    QString instrumentDirectory;
    QString audioFileType;
    int sampleRate;
    int controlRate;

    ProjectSettingsPrivate(ProjectSettings *q)
        :   ObjectPrivate(q)
    {
        clear();
    }

    void clear()
    {
        outputDirectory.clear();
        instrumentDirectory.clear();
        audioFileType.clear();
        sampleRate = 48000;
        controlRate = 4800;
    }
};

#endif // AC_PROJECTSETTINGS_H
