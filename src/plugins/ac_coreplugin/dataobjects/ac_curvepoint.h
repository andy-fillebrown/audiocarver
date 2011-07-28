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

class AcCurvePointPrivate : public AcPointPrivate
{
public:
    quint32 curveType : 16;
    quint32 stretchType : 16;

    AcCurvePointPrivate(AcPoint *q)
        :   AcPointPrivate(q)
        ,   curveType(0)
        ,   stretchType(0)
    {}

    virtual ~AcCurvePointPrivate()
    {}
};

class AC_CORE_EXPORT AcCurvePoint : public AcPoint
{
    Q_OBJECT
    Q_ENUMS(CurveType StretchType)
    Q_PROPERTY(CurveType curveType READ curveType WRITE setCurveType)
    Q_PROPERTY(StretchType stretchType READ stretchType WRITE setStretchType)

public:
    enum PropertyIndex {
        CurveTypeIndex = AcPoint::PropertyCount,
        StretchTypeIndex,
        PropertyCount
    };

    enum CurveType {
        LinearCurve,
        BezierCurve
    };

    enum StretchType {
        StartStretch,
        MiddleStretch,
        EndStretch
    };

    AcCurvePoint()
        :   AcPoint(*(new AcCurvePointPrivate(this)))
    {}

    virtual ~AcCurvePoint()
    {}

    CurveType curveType() const
    {
        Q_D(const AcCurvePoint);
        return CurveType(d->curveType);
    }

    void setCurveType(CurveType type)
    {
        Q_D(AcCurvePoint);
        if (type == CurveType(d->curveType))
            return;
        emit aboutToChange(CurveTypeIndex, d->curveType);
        d->curveType = type;
        emit changed(CurveTypeIndex, d->curveType);
        d->addParentChangedFlags(MiObject::ListItemChanged);
    }

    StretchType stretchType() const
    {
        Q_D(const AcCurvePoint);
        return StretchType(d->stretchType);
    }

    void setStretchType(StretchType type)
    {
        Q_D(AcCurvePoint);
        if (type == StretchType(d->stretchType))
            return;
        emit aboutToChange(StretchTypeIndex, d->stretchType);
        d->stretchType = type;
        emit changed(StretchTypeIndex, d->stretchType);
        d->addParentChangedFlags(MiObject::ListItemChanged);
    }

protected:
    AcCurvePoint(AcCurvePointPrivate &dd)
        :   AcPoint(dd)
    {}

private:
    Q_DISABLE_COPY(AcCurvePoint)
    Q_DECLARE_PRIVATE(AcCurvePoint)
    Q_DECLARE_FRIENDS(AcCurvePoint)
};

#endif // AC_CURVEPOINT_H
