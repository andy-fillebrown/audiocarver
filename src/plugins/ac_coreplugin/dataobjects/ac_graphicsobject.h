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

#ifndef AC_GRAPHICSOBJECT_H
#define AC_GRAPHICSOBJECT_H

#include <ac_object.h>

class GraphicsParentPrivate;

class QGraphicsItem;

class GraphicsObjectPrivate;
class AC_CORE_EXPORT GraphicsObject : public Object
{
    Q_OBJECT

public:
    void setParent(Object *parent);

protected:
    GraphicsObject(GraphicsObjectPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(GraphicsObject)
    Q_DECLARE_PRIVATE(GraphicsObject)
};

class GraphicsObjectPrivate : public ObjectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsObject)

public:
    GraphicsObjectPrivate(GraphicsObject *q);

    virtual void updateGraphicsParent() {}
    virtual GraphicsParentPrivate *graphicsParent() const { return 0; }
};

#endif // AC_GRAPHICSOBJECT_H
