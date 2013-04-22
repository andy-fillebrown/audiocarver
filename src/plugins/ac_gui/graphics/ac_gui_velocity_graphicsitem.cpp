/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_gui_velocity_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <mi_core_object_aggregate.h>
#include <idatabaseobjectfactory.h>
#include <igraphicsgrip.h>
#include <igraphicsgriplist.h>
#include <imodelitem.h>
#include <QGraphicsLineItem>
#include <QPen>

using namespace Ac;

namespace Velocity {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   Base::GraphicsItem(aggregate)
    ,   _lineNode(0)
{
    _lineNode = new QGraphicsLineItem;
    _lineNode->setData(0, quintptr(this));
    QPen pen;
    pen.setCosmetic(true);
    _lineNode->setPen(pen);
}

GraphicsItem::~GraphicsItem()
{
    qDelete(_lineNode);
}

void GraphicsItem::initialize()
{
    update(HighlightRole, false);
}

Object::Aggregate *GraphicsItem::aggregate() const
{
    return static_cast<Object::Aggregate*>(Base::GraphicsItem::aggregate());
}

int GraphicsItem::sceneType() const
{
    return ControlScene;
}

int GraphicsItem::transformType() const
{
    return MainTransform;
}

bool GraphicsItem::intersects(const QRectF &rect) const
{
    QLineF line = _lineNode->line();
    if (rect.contains(line.p1()) && rect.contains(line.p2()))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topLeft(), rect.topRight()), 0))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topRight(), rect.bottomRight()), 0))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomRight(), rect.bottomLeft()), 0))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomLeft(), rect.topLeft()), 0))
        return true;
    return false;
}

IGraphicsItem *GraphicsItem::parent() const
{
    return query<IGraphicsItem>(aggregate()->parent);
}

QGraphicsItem *GraphicsItem::findNode(int sceneType, int transformType) const
{
    Q_ASSERT(UnspecifiedScene == sceneType);
    Q_ASSERT(UnspecifiedTransform == transformType);
    return _lineNode;
}

void GraphicsItem::update(int role, const QVariant &value)
{
    QVariant actual_value = value;
    if (PointsRole == role) {
        // The points role should only be passed in by the graphics delegate
        // since the velocity curve doesn't have points in the model data.
        // Use the passed in points to create a valid volume and let the volume
        // role handler take it from there.
        PointList velocity_curve_points = qvariant_cast<PointList>(value);
        actual_value = velocity_curve_points.first().pos.y();
        role = VolumeRole;
    }
    if (VolumeRole == role) {
        IGraphicsItem *pitchcurve_item = parent()->findItem(PitchCurveItem);
        IGraphicsGripList *pitchcurve_griplist = query<IGraphicsGripList>(pitchcurve_item);
        qreal x = 0.0f;
        if (pitchcurve_griplist && !pitchcurve_griplist->grips().isEmpty()) {
            // If the pitch curve grip data is available, use it to set the
            // velocity curve's x coord so it gets updated correctly when being
            // dragged.
            IGraphicsGrip *first_grip = pitchcurve_griplist->grips().first();
            x = first_grip->position().x();
        } else {
            // If the pitch curve grip data is not available, use the model
            // data to get the velocity curve's x coord.
            IModelItem *this_item = query<IModelItem>(this);
            IModelItem *parent_item = this_item->parent();
            if (!parent_item)
                return;
            PointList pitch_points = get<PointList>(parent_item->findItem(PitchCurveItem), PointsRole);
            if (pitch_points.isEmpty())
                return;
            x = pitch_points.first().pos.x();
        }
        x = qMax(qreal(0.0f), x);
        qreal volume = qBound(qreal(0.0f), qvariant_cast<qreal>(actual_value), qreal(1.0f));
        _lineNode->setLine(x, 0.0f, x, volume);
        PointList points;
        points.append(Point(x, volume));
        query<IGraphicsGripList>(this)->update(PointsRole, QVariant::fromValue(points));
        return;
    }
    if (ColorRole == role) {
        QPen pen = _lineNode->pen();
        pen.setColor(qvariant_cast<QColor>(value));
        _lineNode->setPen(pen);
        return;
    }
    if (HighlightRole == role) {
        int highlightType = qvariant_cast<int>(value);
        QPen pen = _lineNode->pen();
        if (0 < highlightType)
            pen.setWidth(3.0f);
        else
            pen.setWidth(1.0f);
        _lineNode->setPen(pen);
        query<IGraphicsGripList>(this)->update(role, value);
        return;
    }
}

}
