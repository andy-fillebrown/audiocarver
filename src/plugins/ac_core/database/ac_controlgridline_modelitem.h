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

#ifndef AC_CONTROLGRIDLINE_MODELITEM_H
#define AC_CONTROLGRIDLINE_MODELITEM_H

#include "ac_gridline_modelitem.h"

namespace ControlGridLine {

class ModelItem : public GridLine::ModelItem
{
public:
    ModelItem(IAggregate *aggregate)
        :   GridLine::ModelItem(aggregate)
    {}

    IUnknown *initialize();

protected:
    int itemType() const;
    bool isTypeOfItem(int itemType) const;
};

}

#endif
