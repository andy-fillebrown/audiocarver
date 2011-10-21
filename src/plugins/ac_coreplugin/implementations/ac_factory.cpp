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

#include "ac_factory.h"

#include <ac_controlcurve.h>
#include <ac_gridline.h>
#include <ac_note.h>
#include <ac_track.h>

Object *Factory::create(int type) const
{
    switch (type) {
    case Ac::TrackItem:
        return new Track;
    case Ac::NoteItem:
        return new Note;
    case Ac::ControlCurveItem:
        return new ControlCurve;
    case Ac::TimeGridLineItem:
        return new TimeGridLine;
    case Ac::PitchGridLineItem:
        return new PitchGridLine;
    case Ac::ControlGridLineItem:
        return new ControlGridLine;
    default:
        return 0;
    }
}
