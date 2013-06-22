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

#ifndef AC_CSOUND_AUDIOENGINE_H
#define AC_CSOUND_AUDIOENGINE_H

#include <QObject>
#include <mi_audioengine_base_audioengine.h>

class IModelItem;

namespace Csound {
namespace Base {

class AudioEnginePrivate : public QObject
{
    Q_OBJECT

protected slots:
    virtual void reset() = 0;
    virtual void dataAboutToBeChanged(IModelItem *item) = 0;
    virtual void dataChanged(IModelItem *item) = 0;
    virtual void itemChanged(IModelItem *item) = 0;
    virtual void compile() = 0;
    virtual void stop() = 0;
};

}

class AudioEnginePrivate;
class AudioEngine : public ::Base::AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    static AudioEngine *instance();

    const AudioEngineSettings &settings() const;
    void setSettings(const AudioEngineSettings &settings);
    int trackCount() const;
    void setTrackCount(int count);
    qreal startTime() const;
    void setStartTime(qreal time);
    bool isStarted() const;
    void start();
    void stop();
    void compile();

private:
    AudioEnginePrivate *d;
};

}

#endif
