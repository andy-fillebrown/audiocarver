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

#include <ac_core_global.h>
#include <mi_sortedlistobject.h>

class AcCurvePoint;

class AC_CORE_EXPORT AcCurve : public MiSortedListObject
{
    Q_OBJECT

public:
    typedef MiSortedListObject::PropertyIndex PropertyIndex;

    virtual ~AcCurve()
    {}

    qreal duration() const;

    virtual bool isSorted() const;
    virtual void sort();

    const QList<AcCurvePoint*> &children() const;

    virtual void removeChild(MiObject *child)
    {
        if (QObject::children().count() == 2)
            return;
        MiSortedListObject::removeChild(child);
    }

    void update();

protected:
    AcCurve(MiSortedListObjectPrivate &dd)
        :   MiSortedListObject(dd)
    {}

private:
    Q_DISABLE_COPY(AcCurve)
    Q_DECLARE_PRIVATE(MiSortedListObject)
};

class AcCurvePrivate : public MiSortedListObjectPrivate
{
    Q_DECLARE_PUBLIC(AcCurve)

public:
    AcCurvePrivate(AcCurve *q, int propertyIndex)
        :   MiSortedListObjectPrivate(q, propertyIndex)
    {}

    virtual ~AcCurvePrivate()
    {}

    virtual void endChange(int i);
    virtual bool isSortProperty(int i) const;
};

#endif // AC_CURVE_H
