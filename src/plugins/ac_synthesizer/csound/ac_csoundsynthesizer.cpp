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
    const QString rootDirName = rootDir.absolutePath() + "/";

    const QString opcodeDir = rootDirName;
    const QByteArray opcodeDir_ba = opcodeDir.toLocal8Bit();
    csoundSetGlobalEnv("OPCODEDIR", opcodeDir_ba.constData());

    if (CSOUND_SUCCESS != csoundPreCompile(csound))
        qDebug() << Q_FUNC_INFO << "Error precompiling";
    else {
        csoundSetHostImplementedAudioIO(csound, 1, 512);

        char first_arg[] = "";
        char output_arg[] = "-odac";
        char displays_arg[] = "-d";

        const QString csd = rootDirName + "testing/moogladder.csd";
        QByteArray csd_ba = csd.toLocal8Bit();
        char *csd_arg = csd_ba.data();
        qDebug() << Q_FUNC_INFO << csd_arg;

        char *args[] = { first_arg, output_arg, displays_arg, csd_arg };
        if (CSOUND_SUCCESS != csoundCompile(csound, sizeof(*args), args))
            qDebug() << Q_FUNC_INFO << "Error compiling";
        else {
            double *samples = csoundGetOutputBuffer(csound);
            const long n = csoundGetOutputBufferSize(csound);
            Q_ASSERT(samples && n);

            while (!csoundPerformBuffer(csound));
        }
    }
    csoundDestroy(csound);
}
