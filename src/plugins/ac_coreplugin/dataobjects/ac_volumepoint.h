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

#ifndef AC_VOLUMEPOINT_H
#define AC_VOLUMEPOINT_H

#include <ac_point.h>

#define AcVolumePointPrivate AcPointPrivate

class AcVolumePoint : public AcPoint
{
    Q_OBJECT

public:
    AcVolumePoint()
        :   AcPoint(*(new AcVolumePointPrivate(this)))
    {}

    virtual ~AcVolumePoint()
    {}

    virtual void setY(qreal y)
    {
        if (1.0f < y)
            y = 1.0f;
        AcPoint::setY(y);
    }

private:
    Q_DISABLE_COPY(AcVolumePoint)
    Q_DECLARE_FRIENDS(AcVolumePoint)
};

#endif // AC_VOLUMEPOINT_H
