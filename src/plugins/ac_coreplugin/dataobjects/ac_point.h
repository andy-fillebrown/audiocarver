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
#include <mi_scopedchange.h>

class QPointF;

class AcPointPrivate : public MiObjectPrivate
{
public:
    qreal x;
    qreal y;

    AcPointPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   x(0.0f)
        ,   y(0.0f)
    {}

    ~AcPointPrivate()
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

    ~AcPoint()
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
        changing(XIndex);
        d->x = x;
    }

    qreal y() const
    {
        Q_D(const AcPoint);
        return d->y;
    }

    virtual void setY(qreal y)
    {
        Q_D(AcPoint);
        if (y < 0.0f)
            y = 0.0f;
        if (d->y == y)
            return;
        changing(YIndex);
        d->y = y;
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

    void set(qreal x, qreal y)
    {
        setX(x);
        setY(y);
    }

    void set(const QPointF &pos);
    QPointF toPointF() const;

protected:
    AcPoint(AcPointPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DISABLE_COPY(AcPoint)
    Q_DECLARE_PRIVATE(AcPoint)
    Q_DECLARE_FRIENDS(AcPoint)
};

#endif // AC_POINT_H
