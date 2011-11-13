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

#ifndef AC_IGRIPITEM_H
#define AC_IGRIPITEM_H

#include <ac_namespace.h>

#include <mi_iunknown.h>

class IEntityItem;

class QPointF;

class IGripItem : public IUnknown
{
public:
    enum { Type = Ac::GripItemInterface };

    enum HighlightType {
        HoverHighlight,
        FullHighlight
    };

    virtual IEntityItem *parentEntityItem() const = 0;
    virtual const QPointF &originalPosition() const = 0;
    virtual void updateOriginalPosition() = 0;
    virtual void setPosition(const QPointF &position) = 0;
    virtual void highlight(HighlightType type = FullHighlight) = 0;
    virtual void unhighlight() = 0;
};

#endif // AC_IGRIPITEM_H
