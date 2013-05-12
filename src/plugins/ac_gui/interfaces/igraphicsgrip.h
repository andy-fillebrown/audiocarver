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

#ifndef IGRAPHICSGRIP_H
#define IGRAPHICSGRIP_H

#include <igraphicseditor.h>
#include "ac_gui_interfaces.h"
#include <QPointF>

class IGraphicsGrip : public IGraphicsEditor
{
public:
    enum { InterfaceType = I::IGraphicsGrip };

    virtual QPointF originalPosition() const = 0;
    virtual QPointF position() const = 0;
    virtual int curveType() const = 0;
    virtual int highlightType() const = 0;

    static bool lessThan(IGraphicsGrip *a, IGraphicsGrip *b)
    {
        const QPointF pos_a = a->position();
        const QPointF pos_b = b->position();
        if (pos_a.x() < pos_b.x())
            return true;
        if (pos_b.x() < pos_a.x())
            return false;
        if (pos_a.y() < pos_b.y())
            return true;
        return false;
    }

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IGraphicsEditor::isTypeOfInterface(interfaceType);
    }
};

#endif
