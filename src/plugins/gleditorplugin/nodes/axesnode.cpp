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

#include "axesnode.h"

#include <glsceneplugin/classes/buffer.h>
#include <glsceneplugin/classes/root.h>

using namespace GL;
using namespace GL::Internal;

namespace GL {
namespace Internal {

class AxesNodePrivate
{
public:
    AxesNode *q;
    VertexSubBuffer *vertexSubBuffer;
    IndexSubBuffer *indexSubBuffer;

    AxesNodePrivate(AxesNode *q)
        :   q(q)
        ,   vertexSubBuffer(new VertexSubBuffer(4, q->root()->vertexBuffer()))
        ,   indexSubBuffer(new IndexSubBuffer(6, q->root()->indexBuffer()))
    {
        VertexArray vertices(vertexSubBuffer);
        vertices[0] = Vertex(0, 0, 0);
        vertices[1] = Vertex(100000.0f, 0, 0);
        vertices[2] = Vertex(0, 100000.0f, 0);
        vertices[3] = Vertex(0, 0, -100000.0f);

        IndexArray indices(indexSubBuffer);
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 0;
        indices[3] = 2;
        indices[4] = 0;
        indices[5] = 3;
    }
};

} // namespace Internal
} // namespace GL

AxesNode::AxesNode(Node *parent)
    :   Node(parent)
    ,   d(new AxesNodePrivate(this))
{
}

AxesNode::~AxesNode()
{
    delete d;  d = 0;
}

void AxesNode::drawLines(bool picking)
{
    Q_UNUSED(picking);

    glColor3f(0, 0, 0);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
}

void AxesNode::drawTriangles(bool picking)
{
    Q_UNUSED(picking);
}
