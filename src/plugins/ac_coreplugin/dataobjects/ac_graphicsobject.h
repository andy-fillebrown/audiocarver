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

#ifndef AC_GRAPHICSOBJECT_H
#define AC_GRAPHICSOBJECT_H

#include <ac_global.h>

#include <mi_uniquelynamedobject.h>

class GraphicsParentPrivate;

class GraphicsObjectPrivate;
class AC_CORE_EXPORT GraphicsObject : public UniquelyNamedObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GraphicsObject)

protected:
    inline GraphicsObject(GraphicsObjectPrivate &dd, QObject *parent);
};

class GraphicsObjectPrivate : public UniquelyNamedObjectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsObject)

public:
    typedef UniquelyNamedObjectPrivate::ModelItem ModelItem;

    GraphicsObjectPrivate(GraphicsObject *q, ModelItem *modelItem)
        :   UniquelyNamedObjectPrivate(q, modelItem)
    {}

    void setParent(Object *parent)
    {
        ObjectPrivate::setParent(parent);
        updateGraphicsParent();
    }

    virtual void updateGraphicsParent()
    {}

    virtual GraphicsParentPrivate *graphicsParent() const
    {
        return 0;
    }
};

inline GraphicsObject::GraphicsObject(GraphicsObjectPrivate &dd, QObject *parent)
    :   UniquelyNamedObject(dd, parent)
{}

#endif // AC_GRAPHICSOBJECT_H
