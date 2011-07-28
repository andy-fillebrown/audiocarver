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

#include <ac_core_global.h>
#include <mi_object.h>

class AcPointPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiObject)

public:
    qreal x;
    qreal y;

    AcPointPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   x(0.0f)
        ,   y(0.0f)
    {}

    virtual ~AcPointPrivate()
    {}
};

class AC_CORE_EXPORT AcPoint : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    enum PropertyIndex {
        XIndex = MiObject::PropertyCount,
        YIndex,
        PropertyCount
    };

    AcPoint()
        :   MiObject(*(new AcPointPrivate(this)))
    {}

    virtual ~AcPoint()
    {}

    qreal x() const
    {
        Q_D(const AcPoint);
        return d->x;
    }

    void setX(qreal x)
    {
        Q_D(AcPoint);
        if (x < 0.0f)
            x = 0.0f;
        if (d->x == x)
            return;
        aboutToChange(XIndex, d->x);
        d->x = x;
        changed(XIndex, d->x);
        d->addParentChangedFlags(MiObject::ListItemSortValueChanged);
    }

    qreal y() const
    {
        Q_D(const AcPoint);
        return d->y;
    }

    void setY(qreal y)
    {
        Q_D(AcPoint);
        if (y < 0.0f)
            y = 0.0f;
        if (d->y == y)
            return;
        aboutToChange(YIndex, d->x);
        d->y = y;
        changed(YIndex, d->x);
        d->addParentChangedFlags(MiObject::ListItemSortValueChanged);
    }

    bool isLessThan(const AcPoint *other) const
    {
        Q_D(const AcPoint);
        if (d->x < other->x())
            return true;
        if (d->x == other->x() && d->y < other->y())
            return true;
        return false;
    }

protected:
    AcPoint(AcPointPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DISABLE_COPY(AcPoint)
    Q_DECLARE_PRIVATE(AcPoint)
};

#endif // AC_POINT_H
