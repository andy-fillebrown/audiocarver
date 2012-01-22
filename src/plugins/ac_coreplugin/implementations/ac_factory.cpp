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

IModelItem *ObjectFactory::create(int type) const
{
    Object *object = 0;
    switch (type) {
    case Ac::TrackItem:
        object = new Track(::parent);
        break;
    case Ac::NoteItem:
        object = new Note(::parent);
        break;
    case Ac::ControlCurveItem:
        object =  new ControlCurve(::parent);
        break;
    case Ac::TimeGridLineItem:
        object = new TimeGridLine(::parent);
        break;
    case Ac::PitchGridLineItem:
        object = new PitchGridLine(::parent);
        break;
    case Ac::ControlGridLineItem:
        object = new ControlGridLine(::parent);
        break;
    default:
        return 0;
    }
    return query<IModelItem>(object);
}

FilerFactory::FilerFactory()
{
    if (!::parent)
        ::parent = new QObject(this);
}

IReader *FilerFactory::createReader(int type) const
{
    switch (type) {
    case Ac::XmlFileFiler:
        return new XmlFileReader(::parent);
    case Ac::XmlCopyFiler:
        return new XmlCopyReader(::parent);
    }
    return 0;
}

IWriter *FilerFactory::createWriter(int type) const
{
    switch (type) {
    case Ac::XmlFileFiler:
        return new XmlFileWriter(::parent);
    case Ac::XmlCopyFiler:
        return new XmlCopyWriter(::parent);
    }
    return 0;
}
