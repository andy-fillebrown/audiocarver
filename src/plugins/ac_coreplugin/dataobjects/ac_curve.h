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

class AcCurvePrivate : public MiSortedListObjectPrivate
{
public:
    AcCurvePrivate(MiSortedListObject *q)
        :   MiSortedListObjectPrivate(q)
    {}

    virtual ~AcCurvePrivate()
    {}

    QList<AcCurvePoint*> &children();
};

class AcCurve : public MiSortedListObject
{
    Q_OBJECT

public:
    typedef MiSortedListObject::PropertyIndex PropertyIndex;

    virtual ~AcCurve()
    {}

    const QList<AcCurvePoint*> &children() const;
    qreal duration() const;

    virtual bool isSorted() const;
    virtual void sort();
    virtual void addChild(MiObject *child);

    virtual void removeChild(MiObject *child)
    {
        if (QObject::children().count() == 2)
            return;
        MiSortedListObject::removeChild(child);
    }

    virtual void update();

protected:
    AcCurve(AcCurvePrivate &dd)
        :   MiSortedListObject(dd)
    {}

private:
    Q_DISABLE_COPY(AcCurve)
    Q_DECLARE_PRIVATE(AcCurve)
};

#endif // AC_CURVE_H
