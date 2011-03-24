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

#include "root.h"

using namespace GL;

Node::Node(QObject *parent)
    :   QObject(parent)
{
}

Node::~Node()
{
}

Root *Node::root() const
{
    if (isRoot())
        return qobject_cast<Root*>(const_cast<Node*>(this));

    Node *parent = qobject_cast<Node*>(this->parent());
    if (parent)
        return parent->root();

    return 0;
}

void Node::drawLines(bool picking)
{
    Q_UNUSED(picking);
}

void Node::drawTriangles(bool picking)
{
    Q_UNUSED(picking);
}

void Node::changeSubArrayId(int from, int to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
}
