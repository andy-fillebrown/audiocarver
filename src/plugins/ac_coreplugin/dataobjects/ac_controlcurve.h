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

#ifndef AC_CONTROLCURVE_H
#define AC_CONTROLCURVE_H

#include <ac_controlpoint.h>
#include <ac_curve.h>

namespace Private {

class AcControlCurvePrivate : public MiObjectListData
{
public:
    int controlType;

    AcControlCurvePrivate(MiObject *q)
        :   MiObjectListData(q)
        ,   controlType(0)
    {}

    virtual ~AcControlCurvePrivate()
    {}
};

} // namespace Private

class AcControlCurve : public AcCurve
{
    Q_OBJECT
    Q_DISABLE_COPY(AcControlCurve)
    Q_DECLARE_PRIVATE(Private::AcControlCurve)
    Q_PROPERTY(int controlType READ controlType WRITE setControlType)

public:
    enum Properties {
        ControlType = MiObjectList::PropertyCount,
        PropertyCount
    };

    enum ControlTypes {
        Volume = 0,
        Pan,
        ControlTypeCount
    };

    explicit AcControlCurve(QObject *parent = 0)
        :   AcCurve(*(new Private::AcControlCurvePrivate(this)), parent)
    {}

    virtual ~AcControlCurve()
    {}

    int controlType() const
    {
        Q_D(const Private::AcControlCurve);
        return d->controlType;
    }

    void setControlType(int controlType)
    {
        Q_D(Private::AcControlCurve);
        if (d->controlType == controlType || controlType < 0 || ControlTypeCount <= controlType)
            return;
        beginChangeProperty(ControlType);
        d->controlType = controlType;
        endChangeProperty(ControlType);
    }
};

#endif // AC_CONTROLCURVE_H
