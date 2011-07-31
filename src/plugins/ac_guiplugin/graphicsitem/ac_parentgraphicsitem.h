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

#ifndef AC_PARENTGRAPHICSITEM_H
#define AC_PARENTGRAPHICSITEM_H

#include <ac_abstractgraphicsitem.h>
#include <mi_object.h>

class MiParentObject;

class AcParentGraphicsItemPrivate : public AcAbstractGraphicsItemPrivate
{
public:
    MiParentObject *dataObject;

    AcParentGraphicsItemPrivate()
        :   dataObject(0)
    {}

    virtual ~AcParentGraphicsItemPrivate()
    {}
};

class AcParentGraphicsItem : public AcAbstractGraphicsItem
{
    Q_OBJECT

public:
    virtual ~AcParentGraphicsItem()
    {}

    virtual MiObject *dataObject() const;
    void setDataObject(MiParentObject *object);

protected:
    AcParentGraphicsItem(AcParentGraphicsItemPrivate &dd, QObject *parent = 0)
        :   AcAbstractGraphicsItem(dd, parent)
    {
        Q_D(AcParentGraphicsItem);
        setDataObject(d->dataObject);
    }

protected slots:
    virtual void updateDataObject(const MiObject::ChangeFlags &flags) = 0;

private:
    Q_DISABLE_COPY(AcParentGraphicsItem)
    Q_DECLARE_PRIVATE(AcParentGraphicsItem)
};

#endif // AC_PARENTGRAPHICSITEM_H
