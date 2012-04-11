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

#include "mi_dataobject.h"

#include <ac_global.h>

class GraphicsParent;

class AC_CORE_EXPORT GraphicsObject : public DataObject
{
    Q_I_DERIVED__AGGREGATOR(GraphicsObject, DataObject)

protected:
    GraphicsObject() {}

    virtual GraphicsParent *graphicsParent() const { return 0; }
    virtual void updateGraphicsParent() {}

    // DataObject

    void setParent(DataObject *parent)
    {
        Base::setParent(parent);
        updateGraphicsParent();
    }
};

#endif // AC_GRAPHICSOBJECT_H
