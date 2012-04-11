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

#ifndef AC_GRAPHICSPARENT_H
#define AC_GRAPHICSPARENT_H

#include "ac_graphicsobject.h"

class QGraphicsItem;

class AC_CORE_EXPORT GraphicsParent : public GraphicsObject
{
    Q_I_DERIVED__AGGREGATOR(GraphicsParent, GraphicsObject)

    QMap<int, QGraphicsItem*> _mainGraphicsItems;
    QMap<int, QGraphicsItem*> _unitXGraphicsItems;
    QMap<int, QGraphicsItem*> _unitYGraphicsItems;

protected:
    GraphicsParent() {}
    ~GraphicsParent();

    void updateGraphicsParent();
};

#endif // AC_GRAPHICSPARENT_H
