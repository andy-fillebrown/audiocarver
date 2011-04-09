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

#ifndef AC_FPOINT_H
#define AC_FPOINT_H

#include <ac_database_global.h>

class AC_DATABASE_EXPORT AcFPoint
{
public:
    AcFPoint(qreal x = 0.0f, qreal y = 0.0f, bool curved = false) : xp(x), yp(y), curvedp(curved) {}

    qreal x() const { return xp; }
    void setX(qreal x) { xp = x; }

    qreal y() const { return yp; }
    void setY(qreal y) { yp = y; }

    bool isCurved() const { return curvedp; }
    void setCurved(bool curve) { curvedp = curve; }

    friend inline bool operator==(const AcFPoint &a, const AcFPoint &b);

private:
    qreal xp;
    qreal yp;
    bool curvedp;
};

inline bool operator==(const AcFPoint &a, const AcFPoint &b)
{
    return a.curvedp == b.curvedp && qFuzzyIsNull(a.xp - b.xp) && qFuzzyIsNull(a.yp - b.yp);
}

#endif // AC_FPOINT_H
