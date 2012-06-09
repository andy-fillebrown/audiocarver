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

#ifndef AC_DATABASE_SCOREGUI_H
#define AC_DATABASE_SCOREGUI_H

#include "ac_database_score.h"

#include <ac_database_scoreobjectgui.h>

namespace Database {

using namespace ScoreObjectGui;

class ScoreGui : public Score
{
    friend class ObjectGuiFactory;

protected:
    ScoreGui()
    {}

    IAggregator *init();

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IParentEntity:
            return appendAggregate((new ParentEntity(this))->init());
        default:
            return Score::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_SCOREGUI_H
