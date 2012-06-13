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

#ifndef AC_DATABASE_NOTE_H
#define AC_DATABASE_NOTE_H

#include "ac_database_scoreobject.h"

namespace Database {

class AC_CORE_EXPORT Note : public ScoreObject
{
    friend class Factory;

protected:
    Note()
    {}

    IAggregator *init();

    class AC_CORE_EXPORT ModelItem : public ScoreObject::ModelItem
    {
        friend class Note;

    protected:
        ModelItem(Note *aggregator)
            :   ScoreObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        int itemType() const
        {
            return Ac::NoteItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (Ac::NoteItem == itemType)
                return true;
            return ScoreObject::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return ScoreObject::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_NOTE_H
