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

#include "glsubarray.h"

using namespace GLScene;
using namespace GLScene::Internal;

namespace GLScene {
namespace Internal {

class GLSubArrayPrivate
{
public:
    int id;
    int offset;
    int count;
    QList<GLNode*> nodes;

    GLSubArrayPrivate(int count)
        :   id(-1)
        ,   offset(-1)
        ,   count(count)
    {
    }

    ~GLSubArrayPrivate()
    {
        count = 0;
        offset = -1;
        id = -1;
    }
};

class GLIndexSubArrayPrivate
{
public:
    GLIndexBuffer *buffer;

    GLIndexSubArrayPrivate(GLBuffer *buffer)
        :   buffer(qobject_cast<GLIndexBuffer*>(buffer))
    {
        Q_ASSERT(this->buffer);
    }

    ~GLIndexSubArrayPrivate()
    {
        buffer = 0;
    }
};

class GLVertexSubArrayPrivate
{
public:
    GLVertexBuffer *buffer;

    GLVertexSubArrayPrivate(GLBuffer *buffer)
        :   buffer(qobject_cast<GLVertexBuffer*>(buffer))
    {
        Q_ASSERT(this->buffer);
    }

    ~GLVertexSubArrayPrivate()
    {
        buffer = 0;
    }
};

} // namespace Internal
} // namespace GLScene

GLSubArray::GLSubArray(GLBuffer *buffer, int count)
    :   QObject(buffer)
    ,   d(new GLSubArrayPrivate(count))
{
    Q_CHECK_PTR(d);
}

GLSubArray::~GLSubArray()
{
    delete d;  d = 0;
}

int GLSubArray::id() const
{
    return d->id;
}

void GLSubArray::setId(int id)
{
    if (id == d->id)
        return;

    int oldId = d->id;
    d->id = id;

    emit idChanged(oldId, id);
}

int GLSubArray::startOffset() const
{
    return d->offset;
}

void GLSubArray::setStartOffset(int offset)
{
    d->offset = offset;
}

int GLSubArray::endOffset() const
{
    return d->offset + d->count;
}

const QList<GLNode*> &GLSubArray::nodes() const
{
    return d->nodes;
}

void GLSubArray::appendNode(GLNode *node)
{
    d->nodes.append(node);

    connect(this, SIGNAL(idChanged(int,int)), node, SLOT(changeSubArrayId(int,int)));
}

void GLSubArray::removeNode(GLNode *node)
{
    d->nodes.removeOne(node);

    if (!d->nodes.contains(node))
        disconnect(this, SIGNAL(idChanged(int,int)), node, SLOT(changeSubArrayId(int,int)));
}

GLIndexSubArray::GLIndexSubArray(GLBuffer *buffer, int count)
    :   GLSubArray(buffer, count)
    ,   d(new GLIndexSubArrayPrivate(buffer))
{
    Q_CHECK_PTR(d);
}

GLIndexSubArray::~GLIndexSubArray()
{
    delete d;  d = 0;
}

void GLIndexSubArray::write(const QVector<quint32> &indices)
{
    d->buffer->write(startOffset(), indices);
}

GLVertexSubArray::GLVertexSubArray(GLBuffer *buffer, int count)
    :   GLSubArray(buffer, count)
    ,   d(new GLVertexSubArrayPrivate(buffer))
{
    Q_CHECK_PTR(d);
}

GLVertexSubArray::~GLVertexSubArray()
{
    delete d;  d = 0;
}

void GLVertexSubArray::write(const QVector<GLVertex> &vertices)
{
    d->buffer->write(startOffset(), vertices);
}
