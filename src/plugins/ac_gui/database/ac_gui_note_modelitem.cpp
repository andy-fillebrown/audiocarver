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

#include "ac_gui_note_modelitem.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace Note {
namespace Gui {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Note::ModelItem(aggregate)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _velocity = factory->create(VelocityItem, this);
}

ModelItem::~ModelItem()
{
    delete _velocity;
}

IModelItem *ModelItem::findItem(int itemType) const
{
    return VelocityItem == itemType ? query<IModelItem>(velocity()) : Note::ModelItem::findItem(itemType);
}

}
}
