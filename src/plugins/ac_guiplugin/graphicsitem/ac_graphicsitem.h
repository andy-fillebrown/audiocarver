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

#ifndef AC_GRAPHICSITEM_H
#define AC_GRAPHICSITEM_H

#include <ac_abstractgraphicsitem.h>

class AcGraphicsItemPrivate : public AcAbstractGraphicsItemPrivate
{
public:
    MiObject *dataObject;

    AcGraphicsItemPrivate()
        :   dataObject(0)
    {}

    virtual ~AcGraphicsItemPrivate()
    {}
};

class AcGraphicsItem : public AcAbstractGraphicsItem
{
    Q_OBJECT

public:
    virtual ~AcGraphicsItem()
    {}

    virtual MiObject *dataObject() const
    {
        Q_D(const AcGraphicsItem);
        return d->dataObject;
    }

    void setDataObject(MiObject *object)
    {
        Q_D(AcGraphicsItem);
        if (d->dataObject == object)
            return;
        AcAbstractGraphicsItem::setDataObject(object);
    }

protected:
    AcGraphicsItem(AcGraphicsItemPrivate &dd, QObject *parent = 0)
        :   AcAbstractGraphicsItem(dd, parent)
    {
        Q_D(AcGraphicsItem);
        setDataObject(d->dataObject);
    }

private:
    Q_DISABLE_COPY(AcGraphicsItem)
    Q_DECLARE_PRIVATE(AcGraphicsItem)
};

#endif // AC_GRAPHICSITEM_H
