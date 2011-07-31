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
#include <QMetaType>

class AcPitchPoint;

#define AcPitchCurvePrivate AcCurvePrivate

class AcPitchCurve : public AcCurve
{
    Q_OBJECT

public:
    explicit AcPitchCurve(int propertyIndex = 0);

    virtual ~AcPitchCurve()
    {}

    const QList<AcPitchPoint*> &children() const;
    virtual void addChild(MiObject *child);

private:
    Q_DISABLE_COPY(AcPitchCurve)
    Q_DECLARE_FRIENDS(AcPitchCurve)
};

Q_DECLARE_METATYPE(AcPitchCurve*)

#endif // AC_PITCHCURVE_H
