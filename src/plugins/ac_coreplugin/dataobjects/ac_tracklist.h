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
#include <mi_listobject.h>

#define AcTrackListPrivate MiListObjectPrivate

class AcTrackList : public MiListObject
{
    Q_OBJECT

public:
    AcTrackList()
        :   MiListObject(*(new AcTrackListPrivate(this)))
    {}

    virtual ~AcTrackList()
    {}

    virtual void addItem(MiObject *item);

private:
    Q_DISABLE_COPY(AcTrackList)
    Q_DECLARE_FRIENDS(AcTrackList)
};

#endif // AC_TRACKLIST_H
