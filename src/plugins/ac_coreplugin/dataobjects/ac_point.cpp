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

#include "ac_point.h"
#include <mi_objectlist.h>

template <> bool MiSortedList<AcPoint>::lessThan(AcPoint *a, AcPoint *b)
{
    qDebug() << Q_FUNC_INFO;

    if (a->x() < b->x())
        return true;
    if (a->x() == b->x() && a->y() < b->y())
        return true;
    return false;
}
