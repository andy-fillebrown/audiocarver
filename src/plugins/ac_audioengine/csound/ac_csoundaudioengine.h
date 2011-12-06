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

class CsoundAudioEngine : public IAudioEngine
{
    Q_OBJECT

public:
   int controlRate() const;
   void setControlRate(int rate);

   int sampleRate() const;
   void setSampleRate(int rate);

   int bitDepth() const;
   void setBitDepth(int depth);

   int bufferSize() const;
   void setBufferSize(int size);

   const QString &deviceName() const;
   void setDeviceName(const QString &name);

   bool isPlaying() const;
   void play();
   void stop();

   void setPlaybackTime(qreal time);
};

#endif // AC_CSOUNDAUDIOENGINE_H
