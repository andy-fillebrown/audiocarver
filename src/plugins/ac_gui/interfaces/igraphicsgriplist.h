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

#ifndef IGRAPHICSGRIPLIST_H
#define IGRAPHICSGRIPLIST_H

#include <igraphicseditor.h>
#include <QList>

class Point;
class IGraphicsGrip;
class QGraphicsItem;

class IGraphicsGripList : public IGraphicsEditor
{
public:
    enum { InterfaceType = I::IGraphicsGripList };

    virtual QGraphicsItem *findNode() const = 0;
    virtual QList<IGraphicsGrip*> grips() const = 0;
    virtual QList<Point> points() const = 0;
    virtual void sort() = 0;

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
