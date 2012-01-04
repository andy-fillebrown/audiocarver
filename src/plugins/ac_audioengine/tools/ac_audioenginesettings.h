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

#ifndef AC_AUDIOENGINESETTINGS_H
#define AC_AUDIOENGINESETTINGS_H

#include <QSharedDataPointer>

class QAudioDeviceInfo;

class QSettings;
class QString;
class QStringList;

template <typename T> class QList;

class AudioEngineSettingsPrivate;
class AudioEngineSettings
{
public:
    AudioEngineSettings();
    AudioEngineSettings(const AudioEngineSettings &other);
    ~AudioEngineSettings();

    AudioEngineSettings &operator=(const AudioEngineSettings &other);

    void read(QSettings *settings);
    void write(QSettings *settings) const;

    const QString &deviceName() const;
    void setDeviceName(const QString &name);

    int sampleSize() const;
    void setSampleSize(int size);

    int sampleRate() const;
    void setSampleRate(int rate);

    int controlRate() const;
    void setControlRate(int rate);

    int bufferSize() const;
    void setBufferSize(int size);

    bool operator==(const AudioEngineSettings &other) const;

private:
    QSharedDataPointer<AudioEngineSettingsPrivate> d;
};

#endif // AC_AUDIOENGINESETTINGS_H
