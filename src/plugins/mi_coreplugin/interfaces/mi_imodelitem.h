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

#ifndef MI_IMODELITEM_H
#define MI_IMODELITEM_H

#include <mi_iunknown.h>
#include <mi_namespace.h>

class QVariant;

class IModelItem : public IUnknown
{
public:
    enum { Type = Mi::ModelItemInterface };

    virtual int type() const = 0;
    virtual IModelItem *parentModelItem() const = 0;
    virtual void setParentModelItem(IModelItem *parent) = 0;
    virtual int modelItemCount() const = 0;
    virtual int modelItemIndex(IModelItem *item) const = 0;
    virtual IModelItem *modelItemAt(int index) const = 0;
    virtual IModelItem *findModelItem(int type) const = 0;
    virtual IModelItem *findModelItemList(int type) const = 0;
    virtual int persistentRoleCount() const = 0;
    virtual int persistentRoleAt(int i) const = 0;
    virtual QVariant data(int role) const = 0;
    virtual bool setData(const QVariant &data, int role) = 0;
    virtual Qt::ItemFlags flags() const = 0;
};

#endif // MI_IMODELITEM_H
