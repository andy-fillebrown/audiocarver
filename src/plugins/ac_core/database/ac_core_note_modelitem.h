/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_CORE_NOTE_MODELITEM_H
#define AC_CORE_NOTE_MODELITEM_H

#include "ac_core_scoreobject_modelitem.h"
#include "ac_core_global.h"

namespace Note {

class AC_CORE_EXPORT ModelItem : public ScoreObject::ModelItem
{
    IAggregate *_pitchCurve;
    IAggregate *_controlCurve;
    enum { ItemCount = 2 };

public:
    ModelItem(IAggregate *aggregate);

protected:
    enum {
        ItemCountOffset = Object::ModelItem::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    void initialize();
    ~ModelItem();

    int itemType() const;
    bool isTypeOfItem(int itemType) const;

    int itemCount() const
    {
        return TotalItemCount;
    }

    int indexOfItem(const IModelItem *item) const;
    IModelItem *itemAt(int i) const;
    IModelItem *findItem(int itemType) const;
};

}

#endif
