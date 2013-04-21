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

#ifndef AC_CORE_GRIDSETTINGS_MODELITEM_H
#define AC_CORE_GRIDSETTINGS_MODELITEM_H

#include <mi_core_object_modelitem.h>

namespace GridSettings {

class Aggregate;

class ModelItem : public Object::ModelItem
{
public:
    ModelItem(IAggregate *aggregate)
        :   Object::ModelItem(aggregate)
    {}

protected:
    Aggregate *aggregate() const;

    int itemType() const;
    bool isTypeOfItem(int itemType) const;
    int itemCount() const;
    int indexOfItem(const IModelItem *item) const;
    IModelItem *itemAt(int i) const;
    IModelItem *findItem(int itemType) const;
    int roleCount() const;
    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(int role, const QVariant &value);
};

}

#endif
