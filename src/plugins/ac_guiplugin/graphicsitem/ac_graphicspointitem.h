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
#include <ac_coreenums.h>
#include <QPointF>

class QGraphicsRectItem;

class AcGraphicsPointItemPrivate;
class AcGraphicsPointItem : public AcScaledGraphicsItem
{
    Q_OBJECT

public:
    ~AcGraphicsPointItem()
    {}

    void updateDataObject(int i, const QVariant &value);
    void updateViewSettings(int i, const QVariant &value);

protected:
    inline AcGraphicsPointItem(AcGraphicsPointItemPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(AcGraphicsPointItem)
    Q_DECLARE_PRIVATE(AcGraphicsPointItem)
};

class AcGraphicsPointItemPrivate : public AcScaledGraphicsItemPrivate
{
    Q_DECLARE_PUBLIC(AcGraphicsPointItem)

public:
    QPointF point;
    Ac::CurveType curveType;
    QGraphicsRectItem *pointItem;

    AcGraphicsPointItemPrivate(AcGraphicsPointItem *q);
    ~AcGraphicsPointItemPrivate();

    void updateTimeScale(qreal scale);
};

inline AcGraphicsPointItem::AcGraphicsPointItem(AcGraphicsPointItemPrivate &dd, QObject *parent)
    :   AcScaledGraphicsItem(dd, parent)
{}

#endif // AC_GRAPHICSPOINTITEM_H
