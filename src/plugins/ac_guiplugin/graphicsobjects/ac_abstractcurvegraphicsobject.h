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

#ifndef AC_CURVEGRAPHICSOBJECT_H
#define AC_CURVEGRAPHICSOBJECT_H

#include "ac_isubentity.h"
#include "ac_ientity.h"

#include <ac_abstractcurvedataobject.h>

#include <ac_graphicsitem.h>
#include <ac_iparententity.h>

class CurveSubEntity : public ISubEntity
{
protected:
    AbstractCurveDataObject *_a;

    CurveSubEntity(AbstractCurveDataObject *aggregator)
        :   _a(aggregator)
    {}

    ~CurveSubEntity();

public:
    virtual IAggregate *init();

protected:
    // ISubEntity
    bool isCurve() const
    {
        return true;
    }

    IParentEntity *parentEntity() const
    {
        return query<IParentEntity>(_a->parent());
    }

    // IAggregate
    IAggregator *aggregator() const
    {
        return _a;
    }
};

class ControlCurveSubEntity : public CurveSubEntity
{
public:
    ControlCurveSubEntity(AbstractCurveDataObject *aggregator)
        :   CurveSubEntity(aggregator)
    {}

    // ISubEntity
    int sceneType() const
    {
        return Ac::ControlScene;
    }
};

class PitchCurveSubEntity : public CurveSubEntity
{
public:
    PitchCurveSubEntity(AbstractCurveDataObject *aggregator)
        :   CurveSubEntity(aggregator)
    {}

    // ISubEntity
    int sceneType() const
    {
        return Ac::PitchScene;
    }
};

class CurveEntity : public IEntity
{
    GraphicsCurveItem *_graphicsCurveItem;

protected:
    AbstractCurveDataObject *_a;

public:
    CurveEntity(AbstractCurveDataObject *aggregator)
        :   _graphicsCurveItem(0)
        ,   _a(aggregator)
    {}

    virtual IAggregate *init();
    ~CurveEntity();

    void setPoints(const PointList &points)
    {
        _graphicsCurveItem->setPoints(points);
    }

    void setColor(uint color)
    {
        _graphicsCurveItem->setColor(QColor(QRgb(color)));
    }

protected:
    GraphicsCurveItem *graphicsCurveItem() const
    {
        return _graphicsCurveItem;
    }

    // IEntity
    void highlight()
    {
        _graphicsCurveItem->highlight();
    }

    void unhighlight()
    {
        _graphicsCurveItem->unhighlight();
    }

    bool intersects(const QRectF &rect) const
    {
        return _graphicsCurveItem->intersects(rect);
    }

    bool isVisible() const
    {
        return _graphicsCurveItem->isVisible();
    }

    // IAggregate
    IAggregator *aggregator() const
    {
        return _a;
    }
};

#endif // AC_CURVEGRAPHICSOBJECT_H
