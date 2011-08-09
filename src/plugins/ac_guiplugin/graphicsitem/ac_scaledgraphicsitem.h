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

#ifndef AC_SCALEDGRAPHICSITEM_H
#define AC_SCALEDGRAPHICSITEM_H

#include <ac_graphicsitem.h>

class AcScaledGraphicsItemPrivate;
class AcScaledGraphicsItem : public AcGraphicsItem
{
    Q_OBJECT

public:
    ~AcScaledGraphicsItem()
    {}

protected:
    inline AcScaledGraphicsItem(AcScaledGraphicsItemPrivate &dd, QObject *parent = 0);

public slots:
    virtual void updateViewSettings(int i, const QVariant &value) = 0;

private:
    Q_DISABLE_COPY(AcScaledGraphicsItem)
    Q_DECLARE_PRIVATE(AcScaledGraphicsItem)
};

class AcScaledGraphicsItemPrivate : public AcGraphicsItemPrivate
{
    Q_DECLARE_PUBLIC(AcScaledGraphicsItem)

public:
    AcScaledGraphicsItemPrivate(AcScaledGraphicsItem *q)
        :   AcGraphicsItemPrivate(q)
    {}

    ~AcScaledGraphicsItemPrivate()
    {}
};

inline AcScaledGraphicsItem::AcScaledGraphicsItem(AcScaledGraphicsItemPrivate &dd, QObject *parent)
    :   AcGraphicsItem(dd, parent)
{}

#endif // AC_SCALEDGRAPHICSITEM_H
