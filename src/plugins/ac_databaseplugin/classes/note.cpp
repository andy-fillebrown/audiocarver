/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "note.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class NotePrivate
{
public:
    FCurve *pitchCurve;
    FCurve *volumeCurve;

    NotePrivate()
        :   pitchCurve(0)
        ,   volumeCurve(0)
    {
    }

    ~NotePrivate()
    {
        volumeCurve = 0;
        pitchCurve = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

Note::Note(QObject *parent)
    :   Object(parent)
    ,   d(new NotePrivate)
{
    Q_CHECK_PTR(d);
}

Note::~Note()
{
    delete d;  d = 0;
}

Database::Object *Note::pitchCurve() const
{
    return d->pitchCurve;
}

void Note::setPitchCurve(Database::Object *curve)
{
    if (pitchCurve() == curve)
        return;

    d->pitchCurve = qobject_cast<FCurve*>(curve);

    emit propertyChanged(propertyIndex("pitchCurve"), this);
}

Database::Object *Note::volumeCurve() const
{
    return d->volumeCurve;
}

void Note::setVolumeCurve(Database::Object *curve)
{
    if (volumeCurve() == curve)
        return;

    d->volumeCurve = qobject_cast<FCurve*>(curve);

    emit propertyChanged(propertyIndex("volumeCurve"), this);
}
