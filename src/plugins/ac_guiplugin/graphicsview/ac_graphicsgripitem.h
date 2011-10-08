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

#ifndef AC_GRAPHICSGRIPITEM_H
#define AC_GRAPHICSGRIPITEM_H

#include <ac_igripitem.h>

#include <ac_graphicsitem.h>

class GraphicsEntityItem;

class GraphicsGripItemPrivate;
class GraphicsGripItem : public GraphicsItem
        ,   public IGripItem
{
public:
    GraphicsGripItem(const QPointF &position);
    ~GraphicsGripItem();

    IEntityItem *parentEntityItem() const;

    // IGrip
    void setPosition(const QPointF &position);

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::GripItemInterface:
            return Q_I(IGripItem);
        default:
            return 0;
        }
    }

private:
    Q_DISABLE_COPY(GraphicsGripItem)

    GraphicsGripItemPrivate *d;
};

#endif // AC_GRAPHICSGRIPITEM_H