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

#include "buffer.h"

#include <glutils/glutils_global.h>

#include <QtOpenGL/QGLBuffer>

using namespace GL;
using namespace GL::Internal;

namespace GL {
namespace Internal {

class SubBufferPrivate
{
public:
    SubBuffer *q;
    int offset;
    int count; // item count (not byte count)
    Buffer *buffer;

    SubBufferPrivate(SubBuffer *q, int count, Buffer *buffer)
        :   q(q)
        ,   offset(0) // set in GLBufferPrivate::initializeSubBuffer
        ,   count(count)
        ,   buffer(buffer)
    {
    }

    ~SubBufferPrivate()
    {
        buffer = 0;
        count = -1;
        offset = -1;
        q = 0;
    }
};

class IndexSubBufferPrivate
{
public:
};

class VertexSubBufferPrivate
{
public:
};

class BufferPrivate
{
public:
    QGLBuffer *buffer;
    int count; // item count (not byte count)

    QList<SubBuffer*> SubBuffers;

    BufferPrivate(int count)
        :   buffer(0)
        ,   count(count)
    {
    }

    ~BufferPrivate()
    {
        SubBuffers.clear();

        count = -1;
        delete buffer;  buffer = 0;
    }

    int itemSize() const
    {
        Q_ASSERT(buffer);
        if (!buffer)
            return 0;

        return buffer->type() == QGLBuffer::IndexBuffer ? sizeof(index) : sizeof(Vertex);
    }

    void initBuffer(QGLBuffer::Type type)
    {
        Q_ASSERT(!buffer);
        Q_ASSERT(type == QGLBuffer::IndexBuffer || type == QGLBuffer::VertexBuffer);

        buffer = new QGLBuffer(type);
        Q_CHECK_PTR(buffer);
        Q_CHECK_GLERROR;

        bool ok = buffer->create();
        Q_ASSERT(ok);
        Q_CHECK_GLERROR;
        if (!ok)
            return;

        buffer->setUsagePattern(QGLBuffer::DynamicDraw);
        Q_CHECK_GLERROR;

        ok = buffer->bind();
        Q_ASSERT(ok);
        Q_CHECK_GLERROR;
        if (!ok)
            return;

        buffer->allocate(count * itemSize());
        Q_CHECK_GLERROR;
    }

    void initSubBuffer(SubBufferPrivate *SubBuffer_d)
    {
        SubBuffer *SubBuffer = SubBuffer_d->q;
        Q_ASSERT(!SubBuffers.contains(SubBuffer));

        // Find space for SubBuffer in buffer.
        if (SubBuffers.isEmpty())
            SubBuffers.append(SubBuffer);
        else {
            SubBuffer_d->offset = SubBuffers.last()->end();
            int i = 1;
            for (;  i < SubBuffers.count();  ++i) {
                if (SubBuffer->end() < SubBuffers.at(i)->offset())
                    break;
                SubBuffer_d->offset = SubBuffers.at(i)->end();
            }
            Q_ASSERT(SubBuffer->end() < count);
            SubBuffers.insert(i, SubBuffer);
        }
    }

    void removeSubBuffer(SubBufferPrivate *SubBuffer_d)
    {
        SubBuffers.removeOne(SubBuffer_d->q);
    }
};

class IndexBufferPrivate
{
public:
};

class VertexBufferPrivate
{
public:
};

} // namespace Internal
} // namespace GL

Buffer::Buffer(int count, QObject *parent)
    :   QObject(parent)
    ,   d(new BufferPrivate(count))
{
    Q_CHECK_PTR(d);
}

Buffer::~Buffer()
{
    delete d;  d = 0;
}

int Buffer::count() const
{
    return d->count;
}

bool Buffer::bind()
{
    return d->buffer->bind();
}

void Buffer::release()
{
    return d->buffer->release();
}

IndexBuffer::IndexBuffer(int count, QObject *parent)
    :   Buffer(count, parent)
    ,   d(new IndexBufferPrivate())
{
    Q_CHECK_PTR(d);

    Buffer::d->initBuffer(QGLBuffer::IndexBuffer);
}

IndexBuffer::~IndexBuffer()
{
    delete d;  d = 0;
}

VertexBuffer::VertexBuffer(int count, QObject *parent)
    :   Buffer(count, parent)
    ,   d(new VertexBufferPrivate())
{
    Q_CHECK_PTR(d);

    Buffer::d->initBuffer(QGLBuffer::VertexBuffer);
}

VertexBuffer::~VertexBuffer()
{
    delete d;  d = 0;
}

SubBuffer::SubBuffer(int count, Buffer *buffer)
    :   QObject(buffer)
    ,   d(new SubBufferPrivate(this, count, buffer))
{
    Q_CHECK_PTR(d);

    d->buffer->d->initSubBuffer(d);
}

SubBuffer::~SubBuffer()
{
    if (d->buffer->d)
        d->buffer->d->removeSubBuffer(d);

    delete d;  d = 0;
}

int SubBuffer::offset() const
{
    return d->offset;
}

int SubBuffer::count() const
{
    return d->count;
}

IndexSubBuffer::IndexSubBuffer(int count, IndexBuffer *indexBuffer)
    :   SubBuffer(count, indexBuffer)
    ,   d(new IndexSubBufferPrivate())
{
    Q_CHECK_PTR(d);
}

IndexSubBuffer::~IndexSubBuffer()
{
    delete d;  d = 0;
}

void IndexSubBuffer::write(const QVector<index> &indices)
{
    QGLBuffer *buffer = SubBuffer::d->buffer->d->buffer;
    Q_ASSERT(buffer);
    if (!buffer)
        return;

    bool ok = buffer->bind();
    Q_ASSERT(ok);
    Q_CHECK_GLERROR;
    if (!ok)
        return;

    buffer->write(offset() * sizeof(index),
                  indices.data(),
                  count() * sizeof(index));
}

VertexSubBuffer::VertexSubBuffer(int count, VertexBuffer *vertexBuffer)
    :   SubBuffer(count, vertexBuffer)
    ,   d(new VertexSubBufferPrivate())
{
    Q_CHECK_PTR(d);
}

VertexSubBuffer::~VertexSubBuffer()
{
    delete d;  d = 0;
}

void VertexSubBuffer::write(const QVector<Vertex> &vertices)
{
    QGLBuffer *buffer = SubBuffer::d->buffer->d->buffer;
    Q_ASSERT(buffer);
    if (!buffer)
        return;

    bool ok = buffer->bind();
    Q_ASSERT(ok);
    Q_CHECK_GLERROR;
    if (!ok)
        return;

    buffer->write(offset() * sizeof(Vertex),
                  vertices.data(),
                  count() * sizeof(Vertex));
}
