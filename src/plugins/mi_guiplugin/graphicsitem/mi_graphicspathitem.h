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

#ifndef MI_GRAPHICSPATHITEM_H
#define MI_GRAPHICSPATHITEM_H

#include <mi_gui_global.h>
#include <QGraphicsPathItem>

class MI_GUI_EXPORT MiGraphicsPathItem : public QGraphicsPathItem
{
public:
    MiGraphicsPathItem(QGraphicsItem *parent = 0)
        :   QGraphicsPathItem(parent)
    {}

    virtual ~MiGraphicsPathItem()
    {}

    virtual QPainterPath shape() const
    {
        return path();
    }
};

#endif // MI_GRAPHICSPATHITEM_H
