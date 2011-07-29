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

static bool lessThan(const AcNote *a, const AcNote *b)
{
    return a->isLessThan(b);
}

QList<AcNote*> &AcNoteListPrivate::items()
{
    return MiSortedListObjectPrivate::items<AcNote>();
}

bool AcNoteList::isSorted() const
{
    const QList<AcNote*> &notes = items();
    for (int i = 1;  i < notes.count();  ++i)
        if (notes[i]->isLessThan(notes[i - 1]))
            return false;
    return true;
}

void AcNoteList::sort()
{
    if (isSorted())
        return;
    Q_D(AcNoteList);
    qSort(d->items(), lessThan);
}

const QList<AcNote*> &AcNoteList::items() const
{
    return reinterpret_cast<const QList<AcNote*>&>(children());
}

void AcNoteList::addItem(MiObject *item)
{
    if (!qobject_cast<AcNote*>(item))
        return;
    MiListObject::addItem(item);
}
