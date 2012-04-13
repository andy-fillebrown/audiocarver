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

#ifndef AC_PITCHCURVE_H
#define AC_PITCHCURVE_H

#include "ac_curve.h"

#include <ac_graphicsparent.h>

class AC_CORE_EXPORT PitchCurve : public Curve
{
    Q_I_DERIVED__AGGREGATOR(PitchCurve, Curve)

protected:
    // Curve
    ScoreObject *scoreObject() const
    {
        return cast<ScoreObject>(parent());
    }

    void conformPoints()
    {
        PointList &pts = points();
        qSort(pts);
        const int n = pts.count();
        for (int i = 0;  i < n;  ++i) {
            Point &pt = pts[i];
            pt.pos.rx() = qMax(qreal(0.0f), pt.pos.x());
            pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(127.0f));
        }
    }

    // GraphicsObject
    void updateGraphicsParent()
    {
        GraphicsParent *parent = graphicsParent();
        graphicsCurveItem()->setParentItem(parent ? parent->mainGraphicsItems()[Ac::PitchScene] : 0);
    }

    // ISubEntity
    class SubEntity : public Base::SubEntity
    {
        Q_I_DERIVED__AGGREGATE(SubEntity)

        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(a()->graphicsParent());
        }

        int sceneType() const
        {
            return Ac::PitchScene;
        }
    };

    // IModelItem
    class ModelItem : public Base::ModelItem
    {
        Q_I_DERIVED__MODEL_ITEM
        Q_I_DERIVED__MODEL_ITEM__ITEM_TYPE(Ac::PitchCurveItem)
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::ISubEntity:
            return Q_I_CREATE__AGGREGATE(SubEntity);
        case I::IModelItem:
            return Q_I_CREATE__AGGREGATE(ModelItem);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

#endif // AC_PITCHCURVE_H
