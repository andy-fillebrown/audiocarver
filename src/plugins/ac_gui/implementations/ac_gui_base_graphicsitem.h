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

#ifndef AC_GUI_BASE_GRAPHICSITEM_H
#define AC_GUI_BASE_GRAPHICSITEM_H

#include <igraphicsitem.h>

class IAggregate;

namespace Base {

class GraphicsItem : public IGraphicsItem
{
    IAggregate *_aggregate;

public:
    void *queryInterface(int interfaceType) const;

protected:
    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    GraphicsItem(IAggregate *aggregate);

    void initialize()
    {}

    void reset()
    {}

    int sceneType() const
    {
        return -1;
    }

    int transformType() const
    {
        return -1;
    }

    IGraphicsItem *parent() const;
    int itemCount() const;
    IGraphicsItem *itemAt(int i) const;
    IGraphicsItem *findItem(int itemType) const;

    bool intersects(const QRectF &rect) const
    {
        return false;
    }

    void update(int role, const QVariant &value)
    {}
};

}

#endif
