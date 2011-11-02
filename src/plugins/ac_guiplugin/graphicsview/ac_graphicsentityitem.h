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

#ifndef AC_GRAPHICSENTITYITEM_H
#define AC_GRAPHICSENTITYITEM_H

#include <ac_ientityitem.h>

#include <ac_graphicsitem.h>

class IEntity;

class GraphicsEntityItemPrivate;
class GraphicsEntityItem : public GraphicsItem
        ,   public IEntityItem
{
public:
    GraphicsEntityItem(IEntity *entity);
    ~GraphicsEntityItem();

    void resetGrips();

    // IEntityItem
    IEntity *entity() const;
    void highlight();
    void unhighlight();
    void startDraggingPoints();
    void updatePoints();
    void finishDraggingPoints();

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::EntityItemInterface:
            return objectToInterface_cast<IEntityItem>(this);
        default:
            return 0;
        }
    }

private:
    Q_DISABLE_COPY(GraphicsEntityItem)
    GraphicsEntityItemPrivate *d;
};

#endif // AC_GRAPHICSENTITYITEM_H
