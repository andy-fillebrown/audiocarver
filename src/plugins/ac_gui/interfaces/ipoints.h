/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef IPOINTS_H
#define IPOINTS_H

#include <iunknown.h>

class Point;
template <typename T> class QList;
typedef QList<Point> PointList;

class IPoints : public IUnknown
{
public:
    enum { InterfaceType = I::IPoints };

    virtual const PointList &points() const = 0;
    virtual void pushPoints(const PointList &points) = 0;
    virtual void popPoints() = 0;
    virtual void setPoints(const PointList &points) = 0;

    void pushPoints()
    {
        pushPoints(points());
    }

    void setPoints()
    {
        setPoints(points());
    }

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif
