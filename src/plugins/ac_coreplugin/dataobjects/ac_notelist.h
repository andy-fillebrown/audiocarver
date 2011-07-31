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

#ifndef AC_NOTELIST_H
#define AC_NOTELIST_H

#include <ac_core_global.h>
#include <mi_sortedlistobject.h>

class AcNote;

#define AcNoteListPrivate MiSortedListObjectPrivate

class AcNoteList : public MiSortedListObject
{
    Q_OBJECT

public:
    explicit AcNoteList(int propertyIndex = 0)
        :   MiSortedListObject(*(new AcNoteListPrivate(this, propertyIndex)))
    {}

    virtual ~AcNoteList()
    {}

    const QList<AcNote*> &children() const;
    virtual bool isSorted() const;
    virtual void sort();

    virtual void addChild(MiObject *item);

private:
    Q_DISABLE_COPY(AcNoteList)
    Q_DECLARE_PRIVATE(AcNoteList)
};

#endif // AC_NOTELIST_H
