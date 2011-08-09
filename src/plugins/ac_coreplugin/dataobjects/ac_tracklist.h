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

#ifndef AC_TRACKLIST_H
#define AC_TRACKLIST_H

#include <ac_core_global.h>
#include <ac_propertyindexes.h>
#include <mi_listobject.h>

class AcTrack;

#define AcTrackListPrivate MiListObjectPrivate

class AC_CORE_EXPORT AcTrackList : public MiListObject
{
    Q_OBJECT

public:
    explicit AcTrackList(int propertyIndex = TrackList::Children);

    ~AcTrackList()
    {}

    const QList<AcTrack*> &children() const;
    void addChild(MiObject *child);

    void removeChild(MiObject *child)
    {
        if (QObject::children().count() == 1)
            return;
        MiListObject::removeChild(child);
    }

private:
    Q_DISABLE_COPY(AcTrackList)
    Q_DECLARE_PRIVATE(AcTrackList)
};

Q_DECLARE_METATYPE(AcTrackList*)

#endif // AC_TRACKLIST_H
