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

#ifndef AC_MIDI_EVENT_H
#define AC_MIDI_EVENT_H

#include "ac_midi_global.h"
#include "ac_midi_namespace.h"
#include <QList>

namespace Midi {

class Event;
typedef QList<Event> EventList;
typedef QList<quint8> EventBytes;

class AC_MIDI_EXPORT Event
{
public:
    enum Type
    {
        NoteOff = 0x80, // 128
        NoteOn = 0x90,  // 144
        PolyPressure = 0xa0,
        ControlChange = 0xb0,
        ProgramChange = 0xc0,
        ChannelPressure = 0xd0,
        PitchBend = 0xe0,
        SysExStart = 0xf0,
        MidiTimeCode = 0xf1,
        SongPosition = 0xf2,
        SongSelect = 0xf3,
        TuneRequest = 0xf6,
        SysExEnd = 0xf7,
        RealTimeClock = 0xf8,
        RealTimeMeasureEnd = 0xf9,
        RealTimeStart = 0xfa,
        RealTimeContinue = 0xfb,
        RealTimeStop = 0xfc,
        RealTimeActiveSense = 0xfe,
        Reset = 0xff,
        Meta = 0xff
    };

    enum Controller
    {
        ControllerLSBMask = 0x20,
        GMBank = 0x00,
        Modulation = 0x01,
        Breath = 0x02,
        Foot = 0x04,
        PortamentoTime = 0x05,
        DataEntry = 0x06,
        MainVolume = 0x07,
        Balance = 0x08,
        Pan = 0x0a,
        Expression = 0x0b,
        General1 = 0x10,
        General2 = 0x11,
        General3 = 0x12,
        General4 = 0x13,
        HoldSwitch = 0x40,
        PortamentoSwitch = 0x41,
        SostenutoSwitch = 0x42,
        SoftSwitch = 0x43,
        HoldSwitch2 = 0x45,
        General5 = 0x50,
        General6 = 0x51,
        General7 = 0x52,
        General8 = 0x53,
        EffectDepth = 0x5b,
        TremeloDepth = 0x5c,
        ChorusDepth = 0x5d,
        CelesteDepth = 0x5e,
        PhaserDepth = 0x5f,
        DataIncrement = 0x60,
        DataDecrement = 0x61,
        NonRpnLSB = 0x62,
        NonRpnMSB = 0x63,
        RpnLSB = 0x64,
        RpnMSB = 0x65,
        ResetControl = 0x79,
        LocalControl = 0x79,
        AllNotesOff = 0x7a,
        OmniOff = 0x7c,
        OmniOn = 0x7d,
        Mono = 0x73,
        Poly = 0x7f
    };

    enum RegisteredParameterNumber
    {
        RpnBendWidth = 0x00,
        RpnFineTune = 0x01,
        RpnCoarseTune = 0x02
    };

    enum MetaType
    {
        MetaSequenceNumber = 0x00,
        MetaText = 0x01,
        MetaCopyright = 0x02,
        MetaInstrument = 0x03,
        MetaTrack = 0x04,
        MetaLyric = 0x05,
        MetaMarker = 0x06,
        MetaCue = 0x07,
        MetaOutputCable = 0x21,
        MetaTrackLoop = 0x2e,
        MetaDataEnd = 0x2f,
        MetaEndOfTrack = 0x2f,
        MetaTempo = 0x51,
        MetaSMPTE = 0x54,
        MetaTimeSignature = 0x58,
        MetaKeySignature = 0x59,
        MetaBeatMarker = 0x7e,
        MetaSequencerSpecific = 0x7f,
        MetaNoOp = 0x7f
    };

    Event(quint64 tick, EventBytes bytes)
        :   _tick(tick)
        ,   _data(bytes)
    {
        // Change note-on events to note-off if velocity is zero.
        if ((type() == NoteOn) && (data(1) == 0))
            setType(NoteOff);
    }

    quint64 tick() const { return _tick; }
    quint32 size() const { return quint32(_data.size()); }
    quint8 rawData(int i) const { return _data[i]; }
    quint8 channel() const { return _data[0] & 0x0f; }
    quint8 type() const { return _data[0] & 0xf0; }
    quint8 data(int i) const { return _data[i + 1]; }
    void setChannel(quint8 channel) { _data[0] &= 0xf0;  _data[0] += channel; }
    void setType(quint8 type) { _data[0] &= 0x0f;  _data[0] += type; }
    void setData(int i, quint8 byte) { _data[i + 1] = byte; }
    bool operator==(const Event &event);
    bool operator<(const Event &event);

private:
    quint64 _tick;
    EventBytes _data;
};

inline bool Event::operator==(const Event &event)
{
    if (tick() != event.tick())
        return false;
    if (size() != event.size())
        return false;

    quint32 n = size();
    for (quint32 i = 0;  i < n;  i++)
    {
        if (rawData(i) != event.rawData(i))
            return false;
    }

    return true;
}

inline bool Event::operator<(const Event &event)
{
    if (tick() < event.tick())
        return true;
    return false;
}

}

#endif
