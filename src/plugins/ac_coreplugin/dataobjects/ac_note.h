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

#ifndef AC_NOTE_H
#define AC_NOTE_H

#include <ac_scoreobject.h>

class AcNotePrivate : public AcScoreObjectPrivate
{
public:
    AcNotePrivate(AcScoreObject *q)
        :   AcScoreObjectPrivate(q)
    {}

    virtual ~AcNotePrivate()
    {}
};

class AC_CORE_EXPORT AcNote : public AcScoreObject
{
    Q_OBJECT

public:
    AcNote()
    :   AcScoreObject(*(new AcNotePrivate(this)))
    {}

    virtual ~AcNote()
    {}

    bool isLessThan(const AcNote *other) const;

private:
    Q_DISABLE_COPY(AcNote)
    Q_DECLARE_PRIVATE(AcNote)
    Q_DECLARE_FRIENDS(AcNote)
};

#endif // AC_NOTE_H
