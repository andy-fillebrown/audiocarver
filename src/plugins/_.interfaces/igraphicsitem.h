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

#ifndef IGRAPHICSITEM_H
#define IGRAPHICSITEM_H

#include <igraphicseditor.h>

class QGraphicsItem;

class IGraphicsItem : public IGraphicsEditor
{
public:
    enum { InterfaceType = I::IGraphicsItem };

    virtual int sceneType() const = 0;
    virtual int transformType() const = 0;
    virtual IGraphicsItem *parent() const = 0;
    virtual int itemCount() const = 0;
    virtual IGraphicsItem *itemAt(int i) const = 0;
    virtual IGraphicsItem *findItem(int itemType) const = 0;
    virtual QGraphicsItem *findNode(int sceneType = -1, int transformType = -1) const = 0;
    virtual bool intersects(const QRectF &rect) const = 0;

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
