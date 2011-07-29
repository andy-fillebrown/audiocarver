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

#ifndef AC_PITCHPOINT_H
#define AC_PITCHPOINT_H

#include <ac_curvepoint.h>

#define AcPitchPointPrivate AcCurvePointPrivate

class AcPitchPoint : public AcCurvePoint
{
    Q_OBJECT

public:
    AcPitchPoint()
        :   AcCurvePoint(*(new AcPitchPointPrivate(this)))
    {}

    virtual ~AcPitchPoint()
    {}

    virtual void setY(qreal y)
    {
        if (127.0f < y)
            y = 127.0f;
        AcPoint::setY(y);
    }

private:
    Q_DISABLE_COPY(AcPitchPoint)
    Q_DECLARE_FRIENDS(AcPitchPoint)
};

#endif // AC_PITCHPOINT_H
