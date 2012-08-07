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

#ifndef AC_CORE_SCORE_MODELITEM_H
#define AC_CORE_SCORE_MODELITEM_H

#include "ac_core_scoreobject_modelitem.h"

namespace Score {

class ModelItem : public ScoreObject::ModelItem
{
    IAggregate *_tracks;
    IAggregate *_gridSettings;
    IAggregate *_projectSettings;
    IAggregate *_viewSettings;
    enum { ItemCount = 4 };

public:
    enum {
        ItemCountOffset = ScoreObject::ModelItem::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    ModelItem(IAggregate *aggregate)
        :  ScoreObject::ModelItem(aggregate)
        ,   _tracks(0)
        ,   _gridSettings(0)
        ,   _projectSettings(0)
        ,   _viewSettings(0)
    {}

    IUnknown *initialize();

protected:
    ~ModelItem();

    IAggregate *tracks() const
    {
        return _tracks;
    }

    IAggregate *gridSettings() const
    {
        return _gridSettings;
    }

    IAggregate *projectSettings() const
    {
        return _projectSettings;
    }

    IAggregate *viewSettings() const
    {
        return _viewSettings;
    }

    int itemType() const;
    bool isTypeOfItem(int itemType) const;

    int count() const
    {
        return TotalItemCount;
    }

    int indexOf(IModelItem *item) const;
    IModelItem *at(int i) const;
    IModelItem *findItem(int itemType) const;
    IModelItemList *findList(int listType) const;
    void reset();
};

}

#endif
