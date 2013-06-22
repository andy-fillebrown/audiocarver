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

#include "mi_audioengine_utilities.h"
#include <QAudioDeviceInfo>

namespace Mi {
namespace AudioEngine {

QAudioDeviceInfo deviceInfo(const QString &deviceName)
{
    QAudioDeviceInfo device_info;
    bool device_found = false;
    const QList<QAudioDeviceInfo> devs = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach (const QAudioDeviceInfo &cur_info, devs) {
        if (deviceName == cur_info.deviceName()) {
            device_info = cur_info;
            device_found = true;
            break;
        }
    }
    if (!device_found && !devs.isEmpty())
        device_info = devs.first();
    return device_info;
}

int defaultControlRate(int sampleRate)
{
    if (0 == sampleRate)
        return 0;
    int control_rate = sampleRate / 10;
    for (int i = 9;  sampleRate % control_rate;  --i)
        control_rate = sampleRate / i;
    return control_rate;
}

int defaultBufferSize(int sampleRate, int controlRate)
{
    if (0 == controlRate)
        return 0;
    if (sampleRate < controlRate)
        controlRate = sampleRate;
    return 10 * (sampleRate / controlRate);
}

bool controlRateIsValid(int controlRate, int sampleRate)
{
    if (0 == controlRate)
        return false;
    return (sampleRate % controlRate) == 0;
}

bool bufferSizeIsValid(int bufferSize, int sampleRate, int controlRate)
{
    if (0 == sampleRate || 0 == controlRate)
        return false;
    return 0 < bufferSize
            && bufferSize <= sampleRate
            && controlRate <= sampleRate
            && (bufferSize % (sampleRate / controlRate)) == 0;
}

}
}
