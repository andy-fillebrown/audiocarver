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

#include "ac_database_global.h"

namespace AudioCarver {

class FPoint
{
public:
    FPoint() : xp(0.0f), yp(0.0f), curvep(false) {}
    FPoint(float x, float y, bool curvePoint = false) : xp(x), yp(y), curvep(curvePoint) {}
    ~FPoint() {}

    float x() const { return xp; }
    void setX(float x) { xp = x; }

    float y() const { return yp; }
    void setY(float y) { yp = y; }

    bool isCurvePoint() const { return curvep; }
    void setCurvePoint(bool curve) { curvep = curve; }

    friend inline bool operator==(const FPoint &a, const FPoint &b);

private:
    float xp;
    float yp;
    bool curvep;
};

inline bool operator==(const FPoint &a, const FPoint &b)
{
    return a.curvep == b.curvep && qFuzzyIsNull(a.xp - a.xp) && qFuzzyIsNull(a.yp - a.yp);
}

} // namespace AudioCarver

#endif // AC_FPOINT_H
