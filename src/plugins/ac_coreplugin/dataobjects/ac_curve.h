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

#include <mi_objectlist.h>
#include <ac_point.h>

class AcCurve : public MiObjectList
{
    Q_OBJECT
    Q_DISABLE_COPY(AcCurve)
    Q_DECLARE_PRIVATE(Private::MiObjectList)

public:
    typedef MiObjectList::Properties Properties;

    virtual ~AcCurve()
    {}

    const QList<AcPoint*> &points() const
    {
        Q_D(const Private::MiObjectList);
        return d->cast<AcPoint>();
    }

    int pointCount() const
    {
        Q_D(const Private::MiObjectList);
        return d->objects.count();
    }

    AcPoint *pointAt(int i) const
    {
        Q_D(const Private::MiObjectList);
        return d->cast<AcPoint>()[i];
    }

    void insertPoint(int i, AcPoint *point)
    {
        Q_D(Private::MiObjectList);
        d->insert(i, point);
    }

    void appendPoint(AcPoint *point)
    {
        Q_D(Private::MiObjectList);
        d->append(point);
    }

    void removePoint(AcPoint *point)
    {
        Q_D(Private::MiObjectList);
        d->removeOne(point);
    }

protected:
    AcCurve(Private::MiObjectListData &dd, QObject *parent = 0)
        :   MiObjectList(dd, parent)
    {}
};

#endif // AC_CURVE_H
