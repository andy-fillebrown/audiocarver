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

#ifndef AC_CURVEPOINT_H
#define AC_CURVEPOINT_H

#include <ac_point.h>
#include <ac_coreenums.h>
#include <mi_scopedchange.h>

class AcCurvePointPrivate : public AcPointPrivate
{
public:
    qint32 curveType : 16;
    qint32 stretchType : 16;
    qreal previousX;

    AcCurvePointPrivate(AcPoint *q)
        :   AcPointPrivate(q)
        ,   curveType(0)
        ,   stretchType(0)
        ,   previousX(x)
    {}

    ~AcCurvePointPrivate()
    {}
};

class AC_CORE_EXPORT AcCurvePoint : public AcPoint
{
    Q_OBJECT
    Q_PROPERTY(int curveType READ curveType WRITE setCurveType)
    Q_PROPERTY(int stretchType READ stretchType WRITE setStretchType)

public:
    enum StretchType {
        StartStretch,
        MiddleStretch,
        EndStretch,
        NoStretch
    };

    AcCurvePoint()
        :   AcPoint(*(new AcCurvePointPrivate(this)))
    {}

    ~AcCurvePoint()
    {}

    int curveType() const
    {
        Q_D(const AcCurvePoint);
        return d->curveType;
    }

    void setCurveType(int type)
    {
        Q_D(AcCurvePoint);
        if (type == d->curveType)
            return;
        changing(CurvePoint::CurveType);
        d->curveType = type;
    }

    int stretchType() const
    {
        Q_D(const AcCurvePoint);
        return d->stretchType;
    }

    void setStretchType(int type)
    {
        Q_D(AcCurvePoint);
        if (type == d->stretchType)
            return;
        changing(CurvePoint::StretchType);
        d->stretchType = type;
    }

    qreal previousX() const
    {
        Q_D(const AcCurvePoint);
        return d->previousX;
    }

    void update()
    {
        Q_D(AcCurvePoint);
        d->previousX = d->x;
    }

protected:
    AcCurvePoint(AcCurvePointPrivate &dd)
        :   AcPoint(dd)
    {}

private:
    Q_DISABLE_COPY(AcCurvePoint)
    Q_DECLARE_PRIVATE(AcCurvePoint)
};

#endif // AC_CURVEPOINT_H
