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

#include <ac_csoundsynthesizer.h>

#include <csound.h>

#include <QCoreApplication>
#include <QDir>

void CsoundSynthesizer::play()
{
    csoundInitialize(0, 0, 0);

    CSOUND *csound = csoundCreate(0);
    if (!csound) {
        qDebug() << Q_FUNC_INFO << "Error creating";
        return;
    }

    QDir rootDir(QCoreApplication::applicationDirPath());
    rootDir.cdUp();
    const QString rootDirPath = rootDir.absolutePath() + "/";

    const QString opcodeDir = rootDirPath;
    const QByteArray opcodeDir_ba = opcodeDir.toLocal8Bit();
    csoundSetGlobalEnv("OPCODEDIR", opcodeDir_ba.constData());

    int result = 0;
    result = csoundPreCompile(csound);
    if (0 != result)
        qDebug() << Q_FUNC_INFO << "Error precompiling";
    else {
        csoundSetHostImplementedAudioIO(csound, 1, 512);

        char arg_0[] = "";
        char arg_n[] = "-odac";
        char arg_d[] = "-d";

        const QString csd = rootDirPath + "testing/moogladder.csd";
        QByteArray csd_ba = csd.toLocal8Bit();
        char *arg_csd = csd_ba.data();
        qDebug() << arg_csd;

        char *args[] = { arg_0, arg_n, arg_d, arg_csd };
        result = csoundCompile(csound, sizeof(*args), args);
        if (0 != result) {
            qDebug() << Q_FUNC_INFO << "Error compiling";
        } else {
            float *samples = csoundGetOutputBuffer(csound);
            const long n = csoundGetOutputBufferSize(csound);
            Q_ASSERT(samples && n);

            while (!csoundPerformBuffer(csound)) {
                for (int i = 0;  i < n;  ++i)
                    if (0 == (i % 64))
                        qDebug() << i << samples[i];
            }
        }
    }
    csoundDestroy(csound);
}
