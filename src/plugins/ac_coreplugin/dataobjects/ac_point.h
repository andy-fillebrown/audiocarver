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

#ifndef AC_POINT_H
#define AC_POINT_H

#include <mi_object.h>
#include <ac_core_global.h>

namespace Private {

class AcPointPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiObject)

public:
    qreal x;
    qreal y;
    bool curved;

    AcPointPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   x(0.0f)
        ,   y(0.0f)
        ,   curved(false)
    {}

    virtual ~AcPointPrivate()
    {}

    void sortList();
};

} // namespace Private

class AC_CORE_EXPORT AcPoint : public MiListObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AcPoint)
    Q_DECLARE_PRIVATE(Private::AcPoint)
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(bool curved READ isCurved WRITE setCurved)

public:
    enum Properties {
        X = MiObject::PropertyCount,
        Y,
        Curved,
        PropertyCount
    };

    explicit AcPoint(QObject *parent = 0)
        :   MiListObject(*(new Private::AcPointPrivate(this)), parent)
    {}

    virtual ~AcPoint()
    {}

    qreal x() const
    {
        Q_D(const Private::AcPoint);
        return d->x;
    }

    void setX(qreal x)
    {
        Q_D(Private::AcPoint);
        if (d->x == x)
            return;
        beginChangeProperty(X);
        d->x = x;
        endChangeProperty(X);
        sortList();
    }

    qreal y() const
    {
        Q_D(const Private::AcPoint);
        return d->y;
    }

    void setY(qreal y)
    {
        Q_D(Private::AcPoint);
        if (d->y == y)
            return;
        beginChangeProperty(Y);
        d->y = y;
        endChangeProperty(Y);
        sortList();
    }

    bool isCurved() const
    {
        Q_D(const Private::AcPoint);
        return d->curved;
    }

    void setCurved(bool curved)
    {
        Q_D(Private::AcPoint);
        if (d->curved == curved)
            return;
        beginChangeProperty(Y);
        d->curved = curved;
        endChangeProperty(Y);
    }

    static bool lessThan(AcPoint *a, AcPoint *b)
    {
        if (a->x() < b->x())
            return true;
        if (a->x() == b->x() && a->y() < b->y())
            return true;
        return false;
    }
};

#endif // AC_POINT_H
