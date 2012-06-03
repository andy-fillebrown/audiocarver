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

#ifndef AC_DATABASE_NOTEGUI_H
#define AC_DATABASE_NOTEGUI_H

#include "ac_database_note.h"

#include "ac_ichildentity.h"
#include "ac_iparententity.h"

#include <ac_database_scoreobjectgui.h>

namespace Database {

class NoteGui : public Note
{
    friend class ObjectGuiFactory;

protected:
    IAggregator *init();

    class ChildEntity : public IChildEntity
    {
        NoteGui *_aggregator;

    public:
        ChildEntity(NoteGui *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

    protected:
        NoteGui *a() const
        {
            return _aggregator;
        }

        // IChildEntity
        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(a()->parent());
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IParentEntity:
            return appendAggregate((new ScoreObjectGui::ParentEntity(this))->init());
        case I::IChildEntity:
            return appendAggregate((new ChildEntity(this))->init());
        default:
            return Note::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_NOTEGUI_H
