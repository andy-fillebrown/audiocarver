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

#ifndef AC_CORE_NOTE_MODELITEM_H
#define AC_CORE_NOTE_MODELITEM_H

#include "ac_core_scoreobject_modelitem.h"
#include "ac_core_global.h"

namespace Note {

class AC_CORE_EXPORT ModelItem : public ScoreObject::ModelItem
{
public:
    ModelItem(IAggregate *aggregate)
        :   ScoreObject::ModelItem(aggregate)
    {}

    IUnknown *initialize();

protected:
    int itemType() const;
    bool isTypeOfItem(int itemType) const;
};

}

#endif
