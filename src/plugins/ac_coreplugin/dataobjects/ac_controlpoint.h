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

#ifndef AC_CONTROLPOINT_H
#define AC_CONTROLPOINT_H

#include <ac_point.h>

class AcControlPoint : public AcPoint
{
    Q_OBJECT
    Q_DISABLE_COPY(AcControlPoint)
    Q_DECLARE_PRIVATE(Private::AcPoint)

public:
    typedef AcPoint::Properties Properties;

    explicit AcControlPoint(QObject *parent = 0)
        :   AcPoint(parent)
    {}

    virtual ~AcControlPoint()
    {}

protected:
    virtual void endChangeProperty(int propertyIndex)
    {
        if (Y == propertyIndex) {
            Q_D(Private::AcPoint);
            if (d->y < 0.0f)
                d->y = 0.0f;
            else if (1.0f < d->y)
                d->y = 1.0f;
        }
        AcPoint::endChangeProperty(propertyIndex);
    }
};

#endif // AC_CONTROLPOINT_H
