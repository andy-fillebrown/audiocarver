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
#include <mi_objectlist.h>
#include <QMetaType>

namespace Private {

class AcControlCurveData
{
public:
    int controlType;

    AcControlCurveData()
        :   controlType(0)
    {}
};

} // namespace Private

class AcControlCurve : public MiSortedList<AcControlPoint>
{
    Q_OBJECT
    Q_DISABLE_COPY(AcControlCurve)
    Q_PROPERTY(int controlType READ controlType WRITE setControlType)

public:
    enum Properties {
        ControlType = MiSortedList<AcControlPoint>::PropertyCount,
        PropertyCount
    };

    enum ControlTypes {
        Volume = 0,
        Pan,
        ControlTypeCount
    };

    explicit AcControlCurve(QObject *parent = 0)
        :   MiSortedList<AcControlPoint>(parent)
        ,   d(new Private::AcControlCurveData)
    {}

    virtual ~AcControlCurve()
    {
        delete d;
    }

    int controlType() const
    {
        return d->controlType;
    }

    void setControlType(int controlType)
    {
        if (d->controlType == controlType || controlType < 0 || ControlTypeCount <= controlType)
            return;
        beginChangeProperty(ControlType);
        d->controlType = controlType;
        endChangeProperty(ControlType);
    }

private:
    Private::AcControlCurveData *d;
};

typedef MiList<AcControlCurve> AcControlCurveList;

Q_DECLARE_METATYPE(AcControlCurveList*)

#endif // AC_CONTROLCURVE_H
