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

#include <ac_csoundaudioengine.h>

#include <csound.h>

class CsoundAudioEnginePrivate
{
public:
    QString deviceName;
    int controlRate;
    int sampleRate;
    int sampleSize;
    int bufferSize;
    int trackCount;
    qreal startTime;
    uint started : sizeof(uint);

    CsoundAudioEnginePrivate()
        :   controlRate(0)
        ,   sampleRate(0)
        ,   sampleSize(0)
        ,   bufferSize(0)
        ,   trackCount(0)
        ,   startTime(0.0)
        ,   started(false)
    {}

    void start()
    {
        started = true;

//        csoundInitialize(0, 0, 0);

//        CSOUND *csound = csoundCreate(0);
//        if (!csound) {
//            qDebug() << Q_FUNC_INFO << "Error creating";
//            return;
//        }

//        QDir rootDir(QCoreApplication::applicationDirPath());
//        rootDir.cdUp();
//        const QString rootDirName = rootDir.absolutePath() + "/";

//        const QString opcodeDir = rootDirName;
//        const QByteArray opcodeDir_ba = opcodeDir.toLocal8Bit();
//        csoundSetGlobalEnv("OPCODEDIR", opcodeDir_ba.constData());

//        if (CSOUND_SUCCESS != csoundPreCompile(csound))
//            qDebug() << Q_FUNC_INFO << "Error precompiling";
//        else {
//            csoundSetHostImplementedAudioIO(csound, 1, 512);

//            char first_arg[] = "";
//            char output_arg[] = "-odac";
//            char displays_arg[] = "-d";

//            const QString csd = rootDirName + "testing/moogladder.csd";
//            QByteArray csd_ba = csd.toLocal8Bit();
//            char *csd_arg = csd_ba.data();
//            qDebug() << Q_FUNC_INFO << csd_arg;

//            char *args[] = { first_arg, output_arg, displays_arg, csd_arg };
//            if (CSOUND_SUCCESS != csoundCompile(csound, sizeof(*args), args))
//                qDebug() << Q_FUNC_INFO << "Error compiling";
//            else {
//                double *samples = csoundGetOutputBuffer(csound);
//                const long n = csoundGetOutputBufferSize(csound);
//                Q_ASSERT(samples && n);

//                while (!csoundPerformBuffer(csound));
//            }
//        }
//        csoundDestroy(csound);
    }

    void stop()
    {
        started = false;
    }
};

CsoundAudioEngine::CsoundAudioEngine()
    :   d(new CsoundAudioEnginePrivate)
{}

CsoundAudioEngine::~CsoundAudioEngine()
{
    delete d;
}

int CsoundAudioEngine::controlRate() const
{
    return d->controlRate;
}

void CsoundAudioEngine::setControlRate(int rate)
{
    d->controlRate = rate;
}

int CsoundAudioEngine::sampleRate() const
{
    return d->sampleRate;
}

void CsoundAudioEngine::setSampleRate(int rate)
{
    d->sampleRate = rate;
}

int CsoundAudioEngine::sampleSize() const
{
    return d->sampleSize;
}

void CsoundAudioEngine::setSampleSize(int size)
{
    d->sampleSize = size;
}

int CsoundAudioEngine::bufferSize() const
{
    return d->bufferSize;
}

void CsoundAudioEngine::setBufferSize(int size)
{
    d->bufferSize = size;
}

const QString &CsoundAudioEngine::deviceName() const
{
    return d->deviceName;
}

void CsoundAudioEngine::setDeviceName(const QString &name)
{
    d->deviceName = name;
}

int CsoundAudioEngine::trackCount() const
{
    return d->trackCount;
}

void CsoundAudioEngine::setTrackCount(int count)
{
    d->trackCount = count;
}

qreal CsoundAudioEngine::startTime() const
{
    return d->startTime;
}

void CsoundAudioEngine::setStartTime(qreal time)
{
    d->startTime = time;
}

bool CsoundAudioEngine::isStarted() const
{
    return d->started;
}

void CsoundAudioEngine::start()
{
    d->start();
}

void CsoundAudioEngine::stop()
{
    d->stop();
}
