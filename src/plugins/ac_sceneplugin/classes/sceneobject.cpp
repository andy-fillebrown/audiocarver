/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "sceneobject.h"

#include <databaseplugin/classes/object.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class SceneObjectPrivate
{
public:
    Database::Object *databaseObject;

    SceneObjectPrivate(Database::Object *databaseObject)
        :   databaseObject(databaseObject)
    {
    }

    ~SceneObjectPrivate()
    {
        databaseObject = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

SceneObject::SceneObject(Database::Object *databaseObject, QObject *parent)
    :   QObject(parent)
    ,   d(new SceneObjectPrivate(databaseObject))
{
    setObjectName(databaseObject->objectName());
    connect(databaseObject, SIGNAL(propertyChanged(int)), SLOT(updateProperty(int)));
}

SceneObject::~SceneObject()
{
    delete d;  d = 0;
}

Database::Object *SceneObject::databaseObject() const
{
    return d->databaseObject;
}

void SceneObject::updateProperty(int index)
{
    if (index == 0) {
        setObjectName(d->databaseObject->objectName());
        return;
    }
}
