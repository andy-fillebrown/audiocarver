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
#include <ac_xmlfiler.h>

static QObject *parent = 0;

ObjectFactory::ObjectFactory()
{
    if (!::parent)
        ::parent = new QObject(this);
}

Object *ObjectFactory::create(int type) const
{
    switch (type) {
    case Ac::TrackItem:
        return new Track(::parent);
    case Ac::NoteItem:
        return new Note(::parent);
    case Ac::ControlCurveItem:
        return new ControlCurve(::parent);
    case Ac::TimeGridLineItem:
        return new TimeGridLine(::parent);
    case Ac::PitchGridLineItem:
        return new PitchGridLine(::parent);
    case Ac::ControlGridLineItem:
        return new ControlGridLine(::parent);
    default:
        return 0;
    }
}

FilerFactory::FilerFactory()
{
    if (!::parent)
        ::parent = new QObject(this);
}

IFileReader *FilerFactory::createReader(int type) const
{
    switch (type) {
    case Ac::XmlFiler:
        return new XmlFileReader;
    default:
        return 0;
    }
}

IFileWriter *FilerFactory::createWriter(int type) const
{
    switch (type) {
    case Ac::XmlFiler:
        return new XmlFileWriter;
    default:
        return 0;
    }
}
