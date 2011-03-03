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

#include "track.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class TrackPrivate
{
public:
    Database::ObjectList *notes;

    TrackPrivate()
        :   notes(new Database::ObjectList)
    {
        Q_CHECK_PTR(notes);
    }

    ~TrackPrivate()
    {
        delete notes;  notes = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

Track::Track(QObject *parent)
    :   Object(parent)
    ,   d(new TrackPrivate)
{
    Q_CHECK_PTR(d);
}

Track::~Track()
{
    delete d;  d = 0;
}

Database::ObjectList *Track::notes() const
{
    return d->notes;
}
