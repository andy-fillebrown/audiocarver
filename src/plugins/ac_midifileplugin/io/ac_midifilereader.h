/******************************************************************************
**
**   Copyright 2008, 2009 by Andrew Fillebrown. All rights reserved.
**   andy.fillebrown@gmail.com
**
**   This file is part of the MiQt project.
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 3 of the License, or
**   (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
**
**   Contact andy.fillebrown@gmail.com if any conditions of this licensing are
**   not clear to you.
**
******************************************************************************/

#ifndef AC_MIDIFILEREADER_H
#define AC_MIDIFILEREADER_H

#include <ac_midievent.h>

#include <QObject>

namespace Midi {

struct MeterChange
{
    qreal time;
    uint bpm : bitsizeof(uint) / 2;
    uint denominator : bitsizeof(uint) / 2;
};

}

class MidiFileReaderPrivate;

class AC_MIDIFILE_EXPORT MidiFileReader : public QObject
{
    Q_OBJECT

public:
    explicit MidiFileReader(const QString &fileName = QString(), QObject *parent = 0);
    virtual ~MidiFileReader();

    Midi::Format format() const;
    qint16 trackCount() const;
    qint16 division() const;
    bool isUsingTimeCode() const;
    MidiEventList events(int track = 0);

    qreal tickRate() const;
    qreal ticksToSeconds(quint64 tick);

    const QList<Midi::MeterChange> &meterChanges();

private:
    MidiFileReaderPrivate *d;
};

#endif // AC_MIDIFILEREADER_H
