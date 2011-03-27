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

#include "note.h"

#include <ac_databaseplugin/classes/fcurve.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class NoteData
{
public:
    int pointCount;
    FCurve *pitchCurve;

    NoteData()
        :   pointCount(64)
        ,   pitchCurve(0)
    {}
};

} // namespace Internal
} // namespace AudioCarver

Note::Note(QObject *parent)
    :   Object(parent)
    ,   d(new NoteData)
{}

Note::~Note()
{
    delete d;
}

int Note::pointCount() const
{
    return d->pointCount;
}

void Note::setPointCount(int count)
{
    if (pointCount() == count)
        return;
    d->pointCount = count;
    emit propertyChanged(propertyIndex("pointCount"));
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
    emit propertyChanged(propertyIndex("pitchCurve"));
}
