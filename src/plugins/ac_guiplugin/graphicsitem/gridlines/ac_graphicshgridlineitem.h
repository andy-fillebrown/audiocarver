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

#ifndef AC_GRAPHICSHGRIDLINEITEM_H
#define AC_GRAPHICSHGRIDLINEITEM_H

#include <ac_graphicsgridlineitem.h>

class AcGraphicsHGridLineItemPrivate;
class AcGraphicsHGridLineItem : public AcGraphicsGridLineItem
{
    Q_OBJECT

public:
    ~AcGraphicsHGridLineItem()
    {}

public slots:
    virtual void updateScore(int i) = 0;

protected:
    inline AcGraphicsHGridLineItem(AcGraphicsHGridLineItemPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(AcGraphicsHGridLineItem)
    Q_DECLARE_PRIVATE(AcGraphicsHGridLineItem)
};

class AcGraphicsHGridLineItemPrivate : public AcGraphicsGridLineItemPrivate
{
    Q_DECLARE_PUBLIC(AcGraphicsHGridLineItem)

public:
    AcGraphicsHGridLineItemPrivate(AcGraphicsHGridLineItem *q)
        :   AcGraphicsGridLineItemPrivate(q)
    {}

    ~AcGraphicsHGridLineItemPrivate()
    {}
};

inline AcGraphicsHGridLineItem::AcGraphicsHGridLineItem(AcGraphicsHGridLineItemPrivate &dd, QObject *parent)
    :   AcGraphicsGridLineItem(dd, parent)
{}

#endif // AC_GRAPHICSHGRIDLINEITEM_H
