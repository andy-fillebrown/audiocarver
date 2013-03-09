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

#include "ac_gui_curve_modelitemhelper.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>
#include <imodelitemlist.h>

using namespace Ac;

namespace Curve {
namespace Gui {

ModelItemHelper::ModelItemHelper(IModelItem *curve)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _grips = factory->create(GripListItem, curve);
}

ModelItemHelper::~ModelItemHelper()
{
    delete _grips;
}

IModelItemList *ModelItemHelper::findList(int listType) const
{
    return GripItem == listType ? QUERY(IModelItemList, _grips) : 0;
}

}
}
