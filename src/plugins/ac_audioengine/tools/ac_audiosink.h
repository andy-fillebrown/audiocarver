/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef AC_AUDIOSINK_H
#define AC_AUDIOSINK_H

#include <QThread>

class AudioSinkPrivate;

class QAudioDeviceInfo;
class QAudioFormat;

class PlaybackThread : public QThread
{
    Q_OBJECT

private slots:
    virtual void notify() = 0;
};

class AudioSink : public QObject
{
    Q_OBJECT

public:
    typedef qint64 (Callback)(char *data, qint64 byteCount);

    AudioSink(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback, QObject *parent = 0);
    ~AudioSink();

    QAudioFormat format() const;

    void start();
    void stop();

private:
    AudioSinkPrivate *d;
};

#endif // AC_AUDIOSINK_H
