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

#ifndef AC_VOLUMECURVE_H
#define AC_VOLUMECURVE_H

#include <ac_curve.h>

#define AcVolumeCurvePrivate AcCurvePrivate

class AcVolumeCurve : public AcCurve
{
    Q_OBJECT

public:
    AcVolumeCurve()
        :   AcCurve(*(new AcVolumeCurvePrivate(this)))
    {}

    virtual ~AcVolumeCurve()
    {}

    virtual void addItem(MiObject *item);

private:
    Q_DISABLE_COPY(AcVolumeCurve)
    Q_DECLARE_FRIENDS(AcVolumeCurve)
};

#endif // AC_VOLUMECURVE_H
