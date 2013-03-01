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

#ifndef AC_GUI_CURVE_GRAPHICSITEM_H
#define AC_GUI_CURVE_GRAPHICSITEM_H

#include <ac_gui_base_graphicscurve.h>

class GraphicsCurveNode;
class IAggregate;

namespace Curve {

class GraphicsData : public Base::GraphicsCurve
{
    GraphicsCurveNode *_curveNode;

protected:
    GraphicsData(IAggregate *aggregate);
    ~GraphicsData();

    void initialize();

    GraphicsCurveNode *curveNode() const
    {
        return _curveNode;
    }

    bool intersects(const QRectF &rect) const;
    void highlight(bool on);
    void update(int role, const QVariant &value);
};

}

#endif
