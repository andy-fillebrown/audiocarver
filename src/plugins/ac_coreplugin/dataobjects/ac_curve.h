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

#ifndef AC_CURVE_H
#define AC_CURVE_H

#include <ac_ientity.h>

#include <ac_graphicsitem.h>
#include <ac_graphicsobject.h>

#include <QStack>

class ScoreObject;

class CurvePrivate;
class AC_CORE_EXPORT Curve : public GraphicsObject
        ,   public IEntity
{
    Q_OBJECT
    Q_PROPERTY(PointList points READ points WRITE setPoints)

public:
    virtual ScoreObject *scoreObject() const = 0;

    void setColor(const QColor &color);

    // IEntity
    const PointList &points() const;
    void pushPoints(const PointList &points);
    void popPoints();
    void setPoints(const PointList &points);
    void highlight();
    void unhighlight();
    bool intersects(const QRectF &rect) const;
    bool isVisible() const;

    QList<IEntity*> subEntities(int sceneType) const
    {
        Q_UNUSED(sceneType);
        return QList<IEntity*>();
    }

    // IModelItem
    int persistentRoleAt(int i) const
    {
        if (staticMetaObject.propertyOffset() == i)
            return Ac::PointsRole;
        return Object::persistentRoleAt(i);
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::EntityInterface:
            return objectToInterface_cast<IEntity>(this);
        default:
            return GraphicsObject::query(type);
        }
    }

protected:
    Curve(CurvePrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(Curve)
};

class CurvePrivate : public GraphicsObjectPrivate
{
    Q_DECLARE_PUBLIC(Curve)

public:
    QStack<PointList> pointsStack;
    GraphicsCurveItem *graphicsCurveItem;

    CurvePrivate(Curve *q);
    void init();
    ~CurvePrivate();

    virtual void conformPoints() = 0;
    GraphicsParentPrivate *graphicsParent() const;
};

#endif // AC_CURVE_H
