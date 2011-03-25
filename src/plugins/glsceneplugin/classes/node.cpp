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
using namespace GL::Internal;

namespace GL {
namespace Internal {

class NodePrivate
{
public:
    Node *q;
    Root *root;

    NodePrivate(Node *q)
        :   q(q)
        ,   root(0)
    {
    }
};

} // namespace Internal
} // namespace GL

Node::Node(QObject *parent)
    :   QObject(parent)
    ,   d(new NodePrivate(this))
{
    d->root = root();
}

Node::~Node()
{
    delete d;  d = 0;
}

Root *Node::root() const
{
    if (d->root)
        return d->root;

    if (isRoot())
        return qobject_cast<Root*>(const_cast<Node*>(this));

    Node *parent = qobject_cast<Node*>(this->parent());
    if (parent)
        return parent->root();

    return 0;
}

void Node::drawLines(bool picking)
{
    QList<Node*> childNodes = findChildren<Node*>();
    foreach (Node *node, childNodes)
        node->drawLines(picking);
}

void Node::drawTriangles(bool picking)
{
    QList<Node*> childNodes = findChildren<Node*>();
    foreach (Node *node, childNodes)
        node->drawTriangles(picking);
}
