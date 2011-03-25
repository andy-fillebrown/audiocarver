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

#include "root.h"

#include <glsceneplugin/classes/buffer.h>

#include <glutils/glutils_global.h>

#include <QtOpenGL/QGLBuffer>

using namespace GL;
using namespace GL::Internal;

namespace GL {
namespace Internal {

class RootPrivate
{
public:
    Root *q;
    VertexBuffer *vertexBuffer;
    IndexBuffer *indexBuffer;

    RootPrivate(Root *q)
        :   q(q)
        ,   vertexBuffer(0)
        ,   indexBuffer(0)
    {
    }

    ~RootPrivate()
    {
        q = 0;
    }
};

} // namespace Internal
} // namespace GL

Root::Root(QObject *parent)
    :   Node(parent)
    ,   d(new RootPrivate(this))
{
    Q_CHECK_PTR(d);
}

Root::~Root()
{
    destroyBuffers();
    delete d;  d = 0;
}

void Root::initializeBuffers(int vertexCount, int indexCount)
{
    d->vertexBuffer = new VertexBuffer(vertexCount);
    d->indexBuffer = new IndexBuffer(indexCount);
}

void Root::destroyBuffers()
{
    delete d->indexBuffer;  d->indexBuffer = 0;
    delete d->vertexBuffer;  d->vertexBuffer = 0;
}

void Root::drawLines(bool picking)
{
    bool ok = vertexBuffer()->bind();
    Q_ASSERT(ok);

    ok = indexBuffer()->bind();
    Q_ASSERT(ok);

    glVertexPointer(3, GL_FLOAT, 16, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    Node::drawLines(picking);
}

void Root::drawTriangles(bool picking)
{
    bool ok = vertexBuffer()->bind();
    Q_ASSERT(ok);

    ok = indexBuffer()->bind();
    Q_ASSERT(ok);

    glVertexPointer(3, GL_FLOAT, 16, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    Node::drawTriangles(picking);
}

VertexBuffer *Root::vertexBuffer() const
{
    Q_ASSERT(d->vertexBuffer); // forgot to call initializeBuffers?
    return d->vertexBuffer;
}

IndexBuffer *Root::indexBuffer() const
{
    Q_ASSERT(d->indexBuffer); // forgot to call initializeBuffers?
    return d->indexBuffer;
}
