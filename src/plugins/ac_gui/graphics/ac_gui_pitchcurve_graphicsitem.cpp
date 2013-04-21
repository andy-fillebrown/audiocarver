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

#include "ac_gui_pitchcurve_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <igraphicsitem.h>
#include <imodelitem.h>

using namespace Ac;

namespace PitchCurve {

int GraphicsItem::sceneType() const
{
    return PitchScene;
}

void GraphicsItem::update(int role, const QVariant &value)
{
    QVariant actual_value = value;
    if (PointsRole == role) {
        IGraphicsItem *note_gitem = parent();
        IModelItem *note_item = query<IModelItem>(note_gitem);
        note_gitem->update(VolumeRole, note_item->getValue(VolumeRole));
        PointList points = qvariant_cast<PointList>(value);
        const int point_count = points.count();
        for (int i = 0;  i < point_count;  ++i) {
            Point &point = points[i];
            point.pos.ry() = qBound(qreal(0.0f), point.pos.ry(), qreal(127.0f));
        }
        actual_value = QVariant::fromValue(points);
    }
    Curve::GraphicsItem::update(role, actual_value);
}

}
