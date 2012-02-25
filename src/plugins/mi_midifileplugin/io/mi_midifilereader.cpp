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

// The following code is a Qt-style translation based on the code written by
//  Gary P. Scavone for the Synthesis Toolkit (STK).

#include "mi_midifilereader.h"

#include <mi_midievent.h>

#include <QFile>

#include <QtEndian>

static void midifilereader_error(const QString &error)
{
    qDebug() << qPrintable(error);
}

#define MIDIFILEREADER_ERROR(x) \
    midifilereader_error(QString("%1 (%2): %3") \
        .arg(Q_FUNC_INFO) \
        .arg(__LINE__) \
        .arg(x))

struct TempoChange
{
    quint64 tick;
    qreal secondsPerTick;
};

class MidiFileTickConverter
{
public:
    MidiFileTickConverter(MidiFileReader *reader);

    qreal ticksToSeconds(quint64 tick);

private:
    void createTempoMap();
    void rewind();

    MidiFileReader *reader;
    QList<TempoChange> tempoChanges;
    quint64 curTick;
    qreal curTime;
    int curTempoChangeIndex;
    quint64 curTempoChangeEndTick;
};

class MidiFileReaderPrivate
{
public:
    MidiFileReaderPrivate(const QString &fileName);

    void rewind(int track = 0);
    quint64 nextEvent(MidiEventBytes &data, int track = 0);

    QFile file;
    Midi::Format format;
    qint16 trackCount;
    qint16 division;
    bool isUsingTimeCode;

    MidiFileTickConverter *tickConverter;

private:
    QString readString(int size);
    qint16 readValue16();
    qint32 readValue32();
    quint64 readVariableLength();

    QList<quint64> trackPointers;
    QList<quint64> trackOffsets;
    QList<quint64> trackLengths;
    QList<quint64> trackCounters;
    QList<quint8> trackStatusBytes;
};

MidiFileReaderPrivate::MidiFileReaderPrivate(const QString &fileName)
    :   file(fileName)
    ,   format(Midi::Format0)
    ,   trackCount(0)
    ,   division(0)
    ,   isUsingTimeCode(false)
    ,   tickConverter(0)
{
    // Open the file.
    if (!file.open(QIODevice::ReadOnly)) {
        MIDIFILEREADER_ERROR(QString("could not open MIDI file %1").arg(file.fileName()));
        return;
    }

    // Parse the header data.
    if ("MThd" != readString(4)) {
        MIDIFILEREADER_ERROR("error in MIDI file track header");
        return;
    }
    if (6 != readValue32()) {
        MIDIFILEREADER_ERROR("error in MIDI file header length");
        return;
    }

    // Read the MIDI file format.
    format = Midi::Format(readValue16());
    if (Midi::Format0 != format
            && Midi::Format1 != format) {
        MIDIFILEREADER_ERROR("MIDI file types 0 and 1 are the only formats supported");
        return;
    }

    // Read the track count.
    trackCount = readValue16();
    if (-1 == trackCount) {
        MIDIFILEREADER_ERROR("error reading MIDI track count");
        return;
    }
    if (Midi::Format0 == format
            && 1 != trackCount) {
        MIDIFILEREADER_ERROR("invalid MIDI file format 0 track count");
        return;
    }

    // Read the beat division.
    division = readValue16();
    if (-1 == division) {
        MIDIFILEREADER_ERROR("error reading MIDI file beat division");
        return;
    }

    // Locate the track offsets and lengths.
    for (int i = 0;  i < trackCount;  ++i) {
        if ("MTrk" != readString(4)) {
            MIDIFILEREADER_ERROR("error reading MIDI file track header");
            return;
        }
        qint32 length = readValue32();
        if (-1 == length) {
            MIDIFILEREADER_ERROR("error reading MIDI file track length");
            return;
        }
        trackLengths.append(length);
        trackOffsets.append(long(file.pos()));
        trackPointers.append(long(file.pos()));
        trackStatusBytes.append(0);
        trackCounters.append(0);
        file.seek(file.pos() + length);
    }

    // Determine if timecode is being used or not.
    if (division & 0x8000)
        isUsingTimeCode = true;
}

void MidiFileReaderPrivate::rewind(int track)
{
    if (trackCount <= track) {
        MIDIFILEREADER_ERROR(QString("invalid track argument (%1)").arg(track));
        return;
    }
    trackPointers[track] = trackOffsets[track];
    trackStatusBytes[track] = 0;
    trackCounters[track] = 0;
}

quint64 MidiFileReaderPrivate::nextEvent(MidiEventBytes &event, int track)
{
    quint64 tick = 0;

    if (trackCount <= track) {
        MIDIFILEREADER_ERROR(QString("invalid track argument (%1)").arg(track));
        return 0;
    }

    // Fill 'event' with specified track's next event and return event's time
    // in ticks, assuming internal track pointer is at next event's start.
    // Event size is zero when track ends.
    event.clear();

    // Check for track end.
    if (trackLengths[track] <= (trackPointers[track] - trackOffsets[track]))
        return 0;

    // Read event delta tick and set 'tick' to accumulated delta ticks.
    file.seek(trackPointers[track]);
    const quint64 delta = readVariableLength();
    trackCounters[track] += delta;
    tick = trackCounters[track];

    // Parse event stream to determine event length.
    quint64 bytes = 0;
    quint8 c = 0;
    if (!file.read((char *)&c, 1)) {
        MIDIFILEREADER_ERROR("error reading event stream");
        return 0;
    }
    switch (c) {
    case MidiEvent::Meta: {
        quint64 position = 0;
        trackStatusBytes[track] = 0;
        event.append(c);
        if (!file.read((char *)&c, 1)) {
            MIDIFILEREADER_ERROR("error reading event stream");
            return 0;
        }
        event.append(c);
        position = quint64(file.pos());
        bytes = readVariableLength();
        bytes += (((quint64)file.pos()) - position);
        file.seek(position);
        break;
    }
    case MidiEvent::SysExStart:
    case MidiEvent::SysExEnd: {
        trackStatusBytes[track] = 0;
        event.append(c);
        quint64 position = quint64(file.pos());
        bytes = readVariableLength();
        bytes += (((quint64)file.pos()) - position);
        file.seek(position);
        break;
    }
    // Everything else should be channel events.
    default: {
        if (c & 0x80) {
            // Status byte is not running status.
            if (0xf0 < c) {
                MIDIFILEREADER_ERROR("invalid channel event");
                return 0;
            }
            trackStatusBytes[track] = c;
            event.append(c);
            c &= 0xF0;
            if ((c == 0xc0) || (c == 0xd0))
                bytes = 1;
            else
                bytes = 2;
        } else if (trackStatusBytes[track] & 0x80) {
            // Status byte is running status.
            event.append(trackStatusBytes[track]);
            event.append(c);
            c = trackStatusBytes[track] & 0xf0;
            if ((c != 0xc0) && (c != 0xd0))
                bytes = 1;
        } else {
            MIDIFILEREADER_ERROR("invalid status byte");
            return 0;
        }
    }
    }

    // Read rest of data into event's bytes.
    for (quint64 i = 0;  i < bytes;  ++i) {
        if (!file.read((char *)&c, 1)) {
            MIDIFILEREADER_ERROR("error reading event data");
            return 0;
        }
        event.append(c);
    }

    // Save the current track position and return 'tick'.
    trackPointers[track] = file.pos();
    return tick;
}

QString MidiFileReaderPrivate::readString(int size)
{
    char b[size + 1];
    if (!file.read(b, size))
        return QString();
    b[size] = 0;
    return QString(b);
}

qint16 MidiFileReaderPrivate::readValue16()
{
    char b[2];
    if (!file.read(b, 2))
        return -1;
    quint16 *p = reinterpret_cast<quint16 *>(b);
    return qFromBigEndian(*p);
}

qint32 MidiFileReaderPrivate::readValue32()
{
    char b[4];
    if (!file.read(b, 4))
        return -1;
    quint32 *p = reinterpret_cast<quint32 *>(b);
    return qFromBigEndian(*p);
}

quint64 MidiFileReaderPrivate::readVariableLength()
{
    quint64 val = 0;
    char c = 0;
    if (!file.read(&c, 1))
        return 0;
    val = quint64(c);
    if (val & 0x80) {
        val &= 0x7f;
        do {
            if (!file.read(&c, 1))
                return 0;
            val = (val << 7) + (c & 0x7f);
        } while (c & 0x80);
    }
    return val;
}

MidiFileReader::MidiFileReader(const QString &fileName, QObject *parent)
    :   QObject(parent)
    ,   d(new MidiFileReaderPrivate(fileName))
{}

MidiFileReader::~MidiFileReader()
{
    delete d;
}

Midi::Format MidiFileReader::format() const
{
    return d->format;
}

qint16 MidiFileReader::trackCount() const
{
    return d->trackCount;
}

qint16 MidiFileReader::division() const
{
    return d->division;
}

bool MidiFileReader::isUsingTimeCode() const
{
    return d->isUsingTimeCode;
}

MidiEventList MidiFileReader::events(int track)
{
    MidiEventList event_list;
    if (track < 0 || d->trackCount <= track) {
        MIDIFILEREADER_ERROR(QString("invalid track (%1)").arg(track));
        return event_list;
    }
    d->rewind(track);
    MidiEventBytes data;
    for (;;) {
        quint64 tick = d->nextEvent(data, track);
        if (data.size() == 0)
            break;
        MidiEvent event(tick, data);
        event_list.append(event);
    }
    return event_list;
}

qreal MidiFileReader::tickRate() const
{
    qreal rate = 0;
    int div = division();
    if (isUsingTimeCode()) {
        // Determine ticks per second from time-code formats.
        rate = -(div & 0x7f00);

        // If frames per second is 29, change it to 29.97.
        if (rate == 29)
            rate = 29.97;

        rate *= div & 0x00ff;
    } else
        // Determine ticks per quarter note.
        rate = div & 0x7fff;

    return rate;
}

qreal MidiFileReader::ticksToSeconds(quint64 tick)
{
    if (!d->tickConverter)
        d->tickConverter = new MidiFileTickConverter(this);
    return d->tickConverter->ticksToSeconds(tick);
}

MidiFileTickConverter::MidiFileTickConverter(MidiFileReader *reader)
    :   reader(reader)
{
    rewind();
}

qreal MidiFileTickConverter::ticksToSeconds(quint64 tick)
{
    // Create tempo change map if not done already.
    if (tempoChanges.size() == 0)
        createTempoMap();

    // Return the current time if the given 'tick' is the same as the current
    // tick.
    if (tick == curTick)
        return curTime;

    // Rewind the tempo map if the given 'tick' comes before the previous tick.
    if (tick < curTick)
        rewind();

    // The given 'tick' is guaranteed to come after the previous tick now.
    // Calculate the time at the given 'tick' per the tempo map, updating
    // the accumulators along the way.
    if (curTempoChangeEndTick < tick) {
        do {
            curTime += tempoChanges[curTempoChangeIndex].secondsPerTick * (curTempoChangeEndTick - curTick);
            curTick = curTempoChangeEndTick;
            curTempoChangeIndex++;
            if ((curTempoChangeIndex + 1) < tempoChanges.size())
                curTempoChangeEndTick = tempoChanges[curTempoChangeIndex + 1].tick;
            else
                curTempoChangeEndTick = 0xffffffff;
        }
        while (curTempoChangeEndTick < tick);
    }
    curTime += tempoChanges[curTempoChangeIndex].secondsPerTick * (tick - curTick);
    curTick = tick;
    return curTime;
}

void MidiFileTickConverter::createTempoMap()
{
    const qreal tick_rate = reader->tickRate();

    // Start with default tempo.
    TempoChange tempo_change;
    tempo_change.tick = 0;
    if (reader->isUsingTimeCode())
        tempo_change.secondsPerTick = tick_rate;
    else
        tempo_change.secondsPerTick = qreal(0.5f) / tick_rate;
    tempoChanges.append(tempo_change);

    // Create rest of tempo changes from track 0.
    MidiEventList events = reader->events(0);
    foreach (MidiEvent event, events) {
        if (6 == event.size()
                && MidiEvent::Meta == event.rawData(0)
                && MidiEvent::MetaTempo == event.data(0)
                && 3 == event.data(1)) {
            const quint32 midi_rate = (event.data(2) << 16) + (event.data(3) << 8) + event.data(4);
            tempo_change.tick = event.tick();
            tempo_change.secondsPerTick = qreal(0.000001 * qreal(midi_rate) / tick_rate);
            tempoChanges.append(tempo_change);
        }
    }
    rewind();

#if MIQT_DEBUG && 0
    qDebug() << "\nTempo Map:";
    for (int i = 0;  i < tempoChanges.size();  i++) {
        TempoChange tempo_change = tempoChanges[i];
        qDebug() <<
                "\ti ==" << i <<
                "\ttick ==" << tempo_change.tick <<
                "\tsecondsPerTick ==" << tempo_change.secondsPerTick;
    }
    qDebug() << "\n";
#endif
}

void MidiFileTickConverter::rewind()
{
    curTick = 0;
    curTime = 0;
    curTempoChangeIndex = 0;
    curTempoChangeEndTick = 0xffffffff;
    if (1 < tempoChanges.size())
        curTempoChangeEndTick = tempoChanges[1].tick;
}
