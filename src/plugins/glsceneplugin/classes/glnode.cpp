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

#include "glnode.h"

#include "glroot.h"

using namespace GLScene;

GLNode::GLNode(QObject *parent)
    :   QObject(parent)
{
}

GLNode::~GLNode()
{
}

GLRoot *GLNode::root() const
{
    if (isRoot())
        return qobject_cast<GLRoot*>(const_cast<GLNode*>(this));

    GLNode *parent = qobject_cast<GLNode*>(this->parent());
    if (parent)
        return parent->root();

    return 0;
}

void GLNode::drawLines(bool picking)
{
}

void GLNode::drawTriangles(bool picking)
{
}

void GLNode::changeSubArrayId(int from, int to)
{
}
