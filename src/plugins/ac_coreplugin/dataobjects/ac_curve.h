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

#include <ac_graphicsitem.h>
#include <ac_graphicsobject.h>
#include <ac_point.h>

class ScoreObject;

class CurvePrivate;
class AC_CORE_EXPORT Curve : public GraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(PointList points READ points WRITE setPoints)

public:
    const PointList &points() const;
    virtual void setPoints(const PointList &points);

    virtual ScoreObject *scoreObject() const = 0;

    // IModelItem
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

protected:
    Curve(CurvePrivate &dd, QObject *parent = 0);

private:
    Q_DISABLE_COPY(Curve)
    Q_DECLARE_PRIVATE(Curve)
};

class CurvePrivate : public GraphicsObjectPrivate
{
    Q_DECLARE_PUBLIC(Curve)

public:
    PointList points;
    GraphicsCurveItem *graphicsCurveItem;

    CurvePrivate(Curve *q);
    ~CurvePrivate();
    virtual void conformPoints() = 0;
    GraphicsParentPrivate *graphicsParent() const;
};

#endif // AC_CURVE_H
