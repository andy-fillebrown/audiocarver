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

#ifndef GRIDSETTINGS_MODELITEM_H
#define GRIDSETTINGS_MODELITEM_H

#include <base/modelitem.h>

namespace GridSettings {

class ModelItem : public Base::ModelItem
{
    IAggregate *_timeGridLines;
    IAggregate *_pitchGridLines;
    IAggregate *_controlGridLines;
    enum { ItemCount = 3 };

public:
    enum {
        ItemCountOffset = Base::ModelItem::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    ModelItem(IAggregate *aggregate)
        :   Base::ModelItem(aggregate)
        ,   _timeGridLines(0)
        ,   _pitchGridLines(0)
        ,   _controlGridLines(0)
    {}

    IUnknown *initialize();

protected:
    ~ModelItem();

    IAggregate *timeGridLines() const
    {
        return _timeGridLines;
    }

    IAggregate *pitchGridLines() const
    {
        return _pitchGridLines;
    }

    IAggregate *controlGridLines() const
    {
        return _controlGridLines;
    }

    int itemType() const;
    bool isTypeOfItem(int itemType) const;

    int count() const
    {
        return TotalItemCount;
    }

    int indexOf(IModelItem *item) const;
    IModelItem *at(int i) const;
    IModelItemList *findList(int listType) const;
    void reset();
};

}

#endif
