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

#include <mi_objectlist.h>
#include <ac_controlpoint.h>
#include <QMetaType>

namespace Private {

class AcControlCurveData
{
public:
    int type;

    AcControlCurveData()
        :   type(0)
    {}
};

} // namespace Private

class AcControlCurve : public MiSortedList<AcControlPoint>
{
    Q_OBJECT
    Q_DISABLE_COPY(AcControlCurve)
    Q_PROPERTY(int type READ type WRITE setType)

public:
    enum Property {
        Type = MiSortedList<AcControlPoint>::PropertyCount,
        PropertyCount
    };

    enum ControlType {
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

    int type() const
    {
        return d->type;
    }

    void setType(int type)
    {
        if (d->type == type || type < 0 || ControlTypeCount <= type)
            return;
        beginChangeProperty(Type);
        d->type = type;
        endChangeProperty(Type);
    }

private:
    Private::AcControlCurveData *d;
};

typedef MiList<AcControlCurve> AcControlCurveList;

Q_DECLARE_METATYPE(AcControlCurveList*)

#endif // AC_CONTROLCURVE_H
