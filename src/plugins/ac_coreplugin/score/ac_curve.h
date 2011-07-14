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

#ifndef AC_CURVE_H
#define AC_CURVE_H

#include <mi_object.h>
#include <ac_core_global.h>

class AcCurve;
class AcPoint;
template <typename T> class MiList;

namespace Private {

class AcCurveData;

} // namespace Private

class AC_CORE_EXPORT AcCurve : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(MiObjectList* points READ pointObjects)

public:
    enum PropertyIndex
    {
        Points = MiObject::PropertyCount,
        PropertyCount
    };

    AcCurve(QObject *parent = 0);
    virtual ~AcCurve();

    MiList<AcPoint> &points() const;

protected:
    virtual MiObject *createObject(const QString &className);

protected slots:
    virtual void updateCurveProperty(int propertyIndex);
    virtual void updatePointProperty(int propertyIndex);
    virtual void updatePoints();

private:
    Q_DISABLE_COPY(AcCurve)
    Private::AcCurveData *d;

    MiObjectList *pointObjects() const;
};

#endif // AC_CURVE_H
