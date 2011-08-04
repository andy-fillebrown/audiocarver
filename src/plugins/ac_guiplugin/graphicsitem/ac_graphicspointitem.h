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

#include <ac_scaledgraphicsitem.h>

class AcGraphicsPointItem;
class AcPoint;
class QGraphicsRectItem;

class AcGraphicsPointItemPrivate : public AcScaledGraphicsItemPrivate
{
public:
    AcGraphicsPointItem *q;
    QGraphicsRectItem *pointItem;

    AcGraphicsPointItemPrivate(AcGraphicsPointItem *q, AcPoint *point);
    virtual ~AcGraphicsPointItemPrivate();
};

class AcGraphicsPointItem : public AcScaledGraphicsItem
{
    Q_OBJECT

public:
    AcGraphicsPointItem(AcPoint *point = 0, QObject *parent = 0);
    virtual ~AcGraphicsPointItem();

    AcPoint *point();

private:
    Q_DISABLE_COPY(AcGraphicsPointItem)
    Q_DECLARE_PRIVATE(AcGraphicsPointItem)
};

#endif // AC_GRAPHICSPOINTITEM_H
