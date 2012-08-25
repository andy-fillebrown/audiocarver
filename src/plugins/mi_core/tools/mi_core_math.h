/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef MI_CORE_MATH_H
#define MI_CORE_MATH_H

#include <qglobal.h>
#include <math.h>

namespace Mi {

inline qreal roundToNearest(const qreal from, const qreal to)
{
    const qreal r = fmod(from, to);
    const qreal td2 = to / qreal(2.0f);
    if (r == 0)
        return from;
    else if (r < td2)
        return from - r;
    else
        return from + (to - r);
}

}

#endif
