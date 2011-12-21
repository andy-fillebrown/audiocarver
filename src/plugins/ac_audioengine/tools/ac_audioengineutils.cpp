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

#include <ac_audioengineutils.h>

#include <QAudioDeviceInfo>

namespace Ac {

QAudioDeviceInfo deviceInfo(const QString &deviceName)
{
    QAudioDeviceInfo device_info;
    const QList<QAudioDeviceInfo> devs = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach (const QAudioDeviceInfo &cur_info, devs) {
        if (deviceName == cur_info.deviceName()) {
            device_info = cur_info;
            break;
        }
    }
    return device_info;
}

} // namespace Ac
