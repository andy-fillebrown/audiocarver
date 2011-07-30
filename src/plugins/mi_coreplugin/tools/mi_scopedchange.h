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

#ifndef MI_SCOPEDCHANGE_H
#define MI_SCOPEDCHANGE_H

#include <mi_object.h>

class ScopedChange
{
public:
    ScopedChange(MiObjectPrivate *d, int i)
        :   d(d)
        ,   i(i)
    {
        d->beginChange(i);
    }

    ~ScopedChange()
    {
        d->endChange(i);
    }

private:
    MiObjectPrivate *d;
    int i;
};

#define changing(i) ScopedChange scopedChange(d, i)

#endif // MI_SCOPEDCHANGE_H
