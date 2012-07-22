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

#ifndef AC_IGRIP_H
#define AC_IGRIP_H

#include <ac_gui_namespace.h>

#include <mi_iunknown.h>

#include <QPointF>

class ISubEntity;

class IGrip : public IUnknown
{
public:
    enum { InterfaceType = I::IGrip };

    static bool lessThan(IGrip *a, IGrip *b)
    {
        if (a->position().x() < b->position().x())
            return true;
        if (b->position().x() < a->position().x())
            return false;
        if (a->position().y() < b->position().y())
            return true;
        return false;
    }

    virtual ISubEntity *entity() const = 0;
    virtual const QPointF &originalPosition() const = 0;
    virtual void updateOriginalPosition() = 0;
    virtual QPointF position() const = 0;
    virtual void setPosition(const QPointF &position) = 0;
    virtual int curveType() const = 0;
    virtual void setCurveType(int curveType) = 0;
    virtual void highlight(Ac::HighlightType type = Ac::FullHighlight) = 0;
    virtual void unhighlight() = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif // AC_IGRIP_H
