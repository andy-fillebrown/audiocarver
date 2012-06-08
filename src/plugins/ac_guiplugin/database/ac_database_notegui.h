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

#include <ac_database_scoreobjectgui.h>

namespace Database {

using namespace ScoreObjectGui;

class NoteGui : public Note
{
    friend class ObjectGuiFactory;

protected:
    NoteGui()
    {}

    IAggregator *init();

    // Object
    void parentChanged(const Object *object, Mi::NotificationFlags notificationFlags)
    {
        if (this == object)
            ScoreObjectGui::parentChanged(this);
        Note::parentChanged(object, notificationFlags);
    }

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IParentEntity:
            return appendAggregate((new ParentEntity(this))->init());
        case I::IChildEntity:
            return appendAggregate((new ChildEntity(this))->init());
        default:
            return Note::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_NOTEGUI_H
