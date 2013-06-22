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

#ifndef MI_AUDIOENGINE_SINK_H
#define MI_AUDIOENGINE_SINK_H

#include <QObject>
#include "mi_audioengine_global.h"

class QAudioDeviceInfo;
class QAudioFormat;

namespace Mi {
namespace AudioEngine {

class SinkPrivate;
class MI_AUDIOENGINE_EXPORT Sink : public QObject
{
    Q_OBJECT

public:
    typedef qint64 (Callback)(char *data, qint64 byteCount);

    Sink(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback, QObject *parent = 0);
    ~Sink();

    QAudioFormat format() const;
    qreal playbackTime() const;
    virtual void start();
    virtual void stop();

protected slots:
    virtual void notify()
    {}

private:
    SinkPrivate *d;
};

}
}

#endif
