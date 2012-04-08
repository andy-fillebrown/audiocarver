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

#ifndef AC_IENTITY_H
#define AC_IENTITY_H

#include <ac_namespace.h>

#include <mi_iunknown.h>

class IPoints;
class ISubEntity;
class Point;

typedef QList<Point> PointList;

class IEntity : public IUnknown
{
public:
    enum { Type = Ac::EntityInterface };

    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
    virtual bool intersects(const QRectF &rect) const = 0;
    virtual bool isVisible() const = 0;
};

class IParentEntity : public IEntity
{
    enum { Type = Ac::ParentEntityInterface };

    virtual QList<ISubEntity*> subEntities(int sceneType) const = 0;
    virtual QList<IPoints*> subEntityPoints(int sceneType) const = 0;
};

class ISubEntity : public IUnknown
{
public:
    enum { Type = Ac::SubEntityInterface };

    virtual IParentEntity *parentEntity() const = 0;
    virtual int sceneType() const = 0;
    virtual bool isCurve() const = 0;
};

class IPoints : public IUnknown
{
public:
    enum { Type = Ac::PointsInterface };

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
};

#endif // AC_IENTITY_H
