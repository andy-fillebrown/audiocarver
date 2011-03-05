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

#include "node.h"

#include <databaseplugin/classes/object.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class NodePrivate
{
public:
    Database::Object *qdb;

    NodePrivate(Database::Object *databaseObject)
        :   qdb(databaseObject)
    {
    }

    ~NodePrivate()
    {
        qdb = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

Node::Node(Database::Object *databaseObject, QObject *parent)
    :   GLScene::GLNode(parent)
    ,   d(new NodePrivate(databaseObject))
{
    setObjectName(databaseObject->objectName());
    connect(databaseObject, SIGNAL(propertyChanged(int)), SLOT(updateProperty(int)));
}

Node::~Node()
{
    delete d;  d = 0;
}

Database::Object *Node::databaseObject() const
{
    return d->qdb;
}

void Node::updateProperty(int index)
{
    if (index == 0) {
        setObjectName(d->qdb->objectName());
        return;
    }
}
