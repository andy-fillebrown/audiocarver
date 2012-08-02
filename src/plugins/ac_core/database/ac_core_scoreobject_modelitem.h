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

#ifndef AC_CORE_SCOREOBJECT_MODELITEM_H
#define AC_CORE_SCOREOBJECT_MODELITEM_H

#include <mi_core_base_modelitem.h>

namespace ScoreObject {

class ModelItem : public Base::ModelItem
{
    IAggregate *_pitchCurve;
    IAggregate *_controlCurves;
    enum { ItemCount = 2 };

public:
    enum {
        ItemCountOffset = Base::ModelItem::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    ModelItem(IAggregate *aggregate);
    IUnknown *initialize();

protected:
    ~ModelItem();

    IAggregate *pitchCurve() const
    {
        return _pitchCurve;
    }

    IAggregate *controlCurves() const
    {
        return _controlCurves;
    }

    bool isTypeOfItem(int itemType) const = 0;
    int count() const;
    int indexOf(IModelItem *item) const;
    IModelItem *at(int i) const;
    IModelItem *findItem(int itemType) const;
    IModelItemList *findList(int listType) const;
};

}

#endif
