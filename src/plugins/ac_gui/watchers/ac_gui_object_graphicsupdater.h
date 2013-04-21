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

#ifndef AC_GUI_OBJECT_GRAPHICSUPDATER_H
#define AC_GUI_OBJECT_GRAPHICSUPDATER_H

#include "mi_core_base_modelitemwatcher.h"

namespace Object {

class GraphicsUpdater : public Base::ModelItemWatcher
{
public:
    GraphicsUpdater(IAggregate *aggregate)
        :   Base::ModelItemWatcher(aggregate)
    {}

protected:
    void initialize();
    void endChangeParent(const IModelItem *child);
    void endChangeData(const IModelItem *item, int role);
};

}

#endif
