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

#ifndef AC_GUI_NOTE_MODELITEM_H
#define AC_GUI_NOTE_MODELITEM_H

#include "ac_core_note_modelitem.h"

namespace Note {
namespace Gui {

class ModelItem : public Note::ModelItem
{
    IAggregate *_velocity;

public:
    ModelItem(IAggregate *aggregate);

protected:
    ~ModelItem();

    IAggregate *velocity() const
    {
        return _velocity;
    }

    IModelItem *findItem(int itemType) const;
};

}
}

#endif
