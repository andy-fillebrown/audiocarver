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

#ifndef AC_CSOUNDAUDIOENGINE_H
#define AC_CSOUNDAUDIOENGINE_H

#include <ac_iaudioengine.h>

class CsoundAudioEnginePrivate;
class CsoundAudioEngine : public IAudioEngine
{
    Q_OBJECT

public:
    CsoundAudioEngine();
    ~CsoundAudioEngine();

    const AudioEngineSettings &settings() const;
    void setSettings(const AudioEngineSettings &settings);

    int trackCount() const;
    void setTrackCount(int count);

    qreal startTime() const;
    void setStartTime(qreal time);

    bool isStarted() const;
    void start();
    void stop();

private:
    CsoundAudioEnginePrivate *d;
};

#endif // AC_CSOUNDAUDIOENGINE_H
