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

#ifndef AC_TRACK_H
#define AC_TRACK_H

#include <ac_scoreobject.h>

class AcNoteList;

class AcTrackPrivate : public AcScoreObjectPrivate
{
public:
    AcNoteList *notes;

    AcTrackPrivate(AcScoreObject *q);

    virtual ~AcTrackPrivate()
    {}

    void init();
};

class AC_CORE_EXPORT AcTrack : public AcScoreObject
{
    Q_OBJECT
    Q_PROPERTY(AcNoteList* notes READ notes)

public:
    enum PropertyIndex {
        NotesIndex = AcScoreObject::PropertyCount,
        PropertyCount
    };

    AcTrack()
        :   AcScoreObject(*(new AcTrackPrivate(this)))
    {
        Q_D(AcTrack);
        d->init();
    }

    virtual ~AcTrack()
    {}

    AcNoteList *notes() const
    {
        Q_D(const AcTrack);
        return d->notes;
    }

private:
    Q_DISABLE_COPY(AcTrack)
    Q_DECLARE_PRIVATE(AcTrack)
    Q_DECLARE_FRIENDS(AcTrack)
};

#endif // AC_TRACK_H
