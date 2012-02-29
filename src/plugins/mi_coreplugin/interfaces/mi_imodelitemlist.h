/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef MI_IMODELITEMLIST_H
#define MI_IMODELITEMLIST_H

#include <mi_iunknown.h>
#include <mi_namespace.h>

class IModelItem;

class IModelItemList : public IUnknown
{
public:
    enum { Type = Mi::ModelItemListInterface };

    virtual int count() const = 0;
    virtual int indexOf(IModelItem *item) = 0;
    virtual void insert(int i, IModelItem *item) = 0;
    virtual bool remove(IModelItem *item) = 0;

    void append(IModelItem *item)
    {
        insert(count(), item);
    }
};

#endif // MI_IMODELITEMLIST_H
