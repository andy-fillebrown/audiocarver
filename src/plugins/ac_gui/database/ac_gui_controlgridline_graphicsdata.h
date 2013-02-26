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

#ifndef AC_GUI_CONTROLGRIDLINE_GRAPHICSDATA_H
#define AC_GUI_CONTROLGRIDLINE_GRAPHICSDATA_H

#include "ac_gui_horizontalgridline_graphicsdata.h"

namespace ControlGridLine {

class GraphicsData : public HorizontalGridLine::GraphicsData
{
public:
    GraphicsData(IAggregate *aggregate)
        :   HorizontalGridLine::GraphicsData(aggregate)
    {}

protected:
    QGraphicsItem *node(int sceneType, int transformType) const;
};

}

#endif
