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

#ifndef AC_GRAPHICSGRIDLINEITEM_H
#define AC_GRAPHICSGRIDLINEITEM_H

#include <QObject>
#include <ac_scene_global.h>

class AcGridLine;
class QColor;
class QGraphicsLineItem;
class QGraphicsTextItem;

namespace Private {

class AcGraphicsGridLineItemData;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsGridLineItem
{
public:
    AcGraphicsGridLineItem(AcGridLine *gridLine = 0);
    virtual ~AcGraphicsGridLineItem();

    AcGridLine *gridLine() const;
    void setGridLine(AcGridLine *gridLine);

    qreal location() const;
    const QColor &color() const;
    const QString &label() const;
    int priority() const;

    QGraphicsLineItem *qGraphicsScoreLineItem() const;
    QGraphicsLineItem *qGraphicsControllerLineItem() const;

private:
    Q_DISABLE_COPY(AcGraphicsGridLineItem)
    Private::AcGraphicsGridLineItemData *d;
};

#endif // AC_GRAPHICSGRIDLINEITEM_H
