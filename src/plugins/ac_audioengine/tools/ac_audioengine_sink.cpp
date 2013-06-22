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

#include "ac_audioengine_sink.h"
#include <ac_core_namespace.h>
#include <idatabase.h>
#include <imodelitem.h>

namespace Ac {
namespace AudioEngine {

Sink::Sink(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback, QObject *parent)
    :   Mi::AudioEngine::Sink(deviceInfo, format, bufferSize, callback, parent)
{}

void Sink::stop()
{
    IDatabase::instance()->rootItem()->set(0.0f, PlaybackTimeRole);
    Mi::AudioEngine::Sink::stop();
}

void Sink::notify()
{
    IDatabase::instance()->rootItem()->set(playbackTime(), PlaybackTimeRole);
}

}
}
