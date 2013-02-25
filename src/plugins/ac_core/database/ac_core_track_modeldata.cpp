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

#include "ac_core_track_modeldata.h"
#include "ac_core_constants.h"
#include <mi_core_utilities.h>
#include <mi_core_scopeddatachange.h>

using namespace Ac;
using namespace Mi;

namespace Track {

ModelData::ModelData(IAggregate *aggregate)
    :   ScoreObject::ModelData(aggregate)
    ,   _color(DEFAULT_TRACK_COLOR)
    ,   _visible(false)
    ,   _recording(false)
{}

bool ModelData::setColor(int color)
{
    if (_color == color)
        return false;
    ScopedDataChange data_change(this, ColorRole);
    _color = color;
    return true;
}

bool ModelData::setInstrument(const QString &instrument)
{
    if (_instrument == instrument)
        return false;
    ScopedDataChange data_change(this, InstrumentRole);
    _instrument = instrument;
    return true;
}

bool ModelData::setVisible(bool visible)
{
    if (_visible == visible)
        return false;
    ScopedDataChange data_change(this, VisibilityRole);
    _visible = visible;
    return true;
}

bool ModelData::setRecording(bool recording)
{
    if (_recording == recording)
        return false;
    ScopedDataChange data_change(this, RecordingRole);
    _recording = recording;
    return true;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return ColorRole;
    case 1:
        return InstrumentRole;
    case 2:
        return VisibilityRole;
    case 3:
        return RecordingRole;
    default:
        return ScoreObject::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case ColorRole:
        return colorFromInt(_color);
    case InstrumentRole:
        return _instrument;
    case VisibilityRole:
        return _visible;
    case RecordingRole:
        return _recording;
    default:
        return ScoreObject::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case ColorRole:
        return setColor(intFromColor(value));
    case InstrumentRole:
        return setInstrument(qvariant_cast<QString>(value));
    case VisibilityRole:
        return setVisible(qvariant_cast<bool>(value));
    case RecordingRole:
        return setRecording(qvariant_cast<bool>(value));
    default:
        return ScoreObject::ModelData::setValue(value, role);
    }
}

}
