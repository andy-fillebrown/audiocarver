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

#ifndef AC_GRAPHICSPOINTITEM_H
#define AC_GRAPHICSPOINTITEM_H

#include <ac_graphicsitem.h>

class AcPoint;
class QGraphicsEllipseItem;

namespace Private {

class AcGraphicsPointItemData : public AcGraphicsItemData
{
public:
    QGraphicsEllipseItem *pointItem;

    AcGraphicsPointItemData(AcPoint *point);
    virtual ~AcGraphicsPointItemData();
};

class AcGraphicsPointItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsPointItem : public AcGraphicsItem
{
    Q_OBJECT

public:
    AcGraphicsPointItem(AcPoint *point = 0, QObject *parent = 0);
    virtual ~AcGraphicsPointItem();

private:
    Q_DISABLE_COPY(AcGraphicsPointItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsPointItem)
};

#endif // AC_GRAPHICSPOINTITEM_H
