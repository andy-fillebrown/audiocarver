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

#ifndef AC_AUDIOENGINE_SINK_H
#define AC_AUDIOENGINE_SINK_H

#include <mi_audioengine_sink.h>
#include "ac_audioengine_global.h"

namespace Ac {
namespace AudioEngine {

class AC_AUDIOENGINE_EXPORT Sink : public Mi::AudioEngine::Sink
{
    Q_OBJECT

public:
    Sink(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback, QObject *parent = 0);

    void stop();

protected slots:
    void notify();
};

}
}

#endif
