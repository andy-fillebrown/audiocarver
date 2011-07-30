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

#include "ac_notelist.h"
#include <ac_note.h>

QList<AcNote*> &AcNoteListPrivate::children()
{
    return MiObjectPrivate::children<AcNote>();
}

bool AcNoteList::isSorted() const
{
    Q_D(const AcNoteList);
    return d->isSorted<AcNote>();
}

void AcNoteList::sort()
{
    Q_D(AcNoteList);
    d->sort<AcNote>();
}

const QList<AcNote*> &AcNoteList::children() const
{
    return reinterpret_cast<const QList<AcNote*>&>(d_ptr->children<AcNote>());
}

void AcNoteList::addChild(MiObject *child)
{
    if (!qobject_cast<AcNote*>(child))
        return;
    MiSortedListObject::addChild(child);
}
