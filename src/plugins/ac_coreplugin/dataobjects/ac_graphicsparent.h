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

#include <ac_graphicsobject.h>

class QGraphicsItem;

class GraphicsParentPrivate;
class AC_CORE_EXPORT GraphicsParent : public GraphicsObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GraphicsParent)

protected:
    inline GraphicsParent(GraphicsParentPrivate &dd, QObject *parent);
};

class GraphicsParentPrivate : public GraphicsObjectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsParent)

public:
    QMap<int, QGraphicsItem*> mainGraphicsItems;
    QMap<int, QGraphicsItem*> unitXGraphicsItems;
    QMap<int, QGraphicsItem*> unitYGraphicsItems;

    typedef GraphicsObjectPrivate::ModelItem ModelItem;

    GraphicsParentPrivate(GraphicsParent *q, ModelItem *modelItem)
        :   GraphicsObjectPrivate(q, modelItem)
    {}

    ~GraphicsParentPrivate();

    void init()
    {
        updateGraphicsParent();
    }

    void updateGraphicsParent();
};

inline GraphicsParent::GraphicsParent(GraphicsParentPrivate &dd, QObject *parent)
    :   GraphicsObject(dd, parent)
{
    dd.init();
}

#endif // AC_GRAPHICSPARENT_H
