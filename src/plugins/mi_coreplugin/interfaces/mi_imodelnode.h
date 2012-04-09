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

#ifndef MI_IMODELNODE_H
#define MI_IMODELNODE_H

#include <mi_iaggregate.h>

class IModelList;

class IModelNode : public IAggregate
{
public:
    enum { Type = Mi::ModelItemInterface };

    virtual int count() const = 0;
    virtual int indexOf(const IModelNode *node) const = 0;
    virtual const IModelNode *at(int i) const = 0;
    virtual const IModelNode *findNode(int type) const = 0;
    virtual const IModelList *findList(int listType) const = 0;
};

#endif // MI_IMODELNODE_H
