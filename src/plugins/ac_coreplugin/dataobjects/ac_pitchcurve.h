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

#ifndef AC_PITCHCURVE_H
#define AC_PITCHCURVE_H

#include <ac_curve.h>

namespace Private {

class AcPitchCurveData;

} // namespace Private

class AC_CORE_EXPORT AcPitchCurve: public AcCurve
{
    Q_OBJECT

public:
    typedef AcCurve::PropertyIndex PropertyIndex;

    AcPitchCurve(QObject *parent = 0);
    virtual ~AcPitchCurve();

protected:
    virtual void updatePoints();

private:
    Q_DISABLE_COPY(AcPitchCurve)
    Private::AcPitchCurveData *d;
};

#endif // AC_PITCHCURVE_H
