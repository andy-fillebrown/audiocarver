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

class ArrayPrivate
{
public:
    Array *q;
    int offset;
    int count; // item count (not byte count)
    Buffer *buffer;

    ArrayPrivate(Array *q, int count, Buffer *buffer)
        :   q(q)
        ,   offset(0) // set in GLBufferPrivate::initializeArray
        ,   count(count)
        ,   buffer(buffer)
    {
    }

    ~ArrayPrivate()
    {
        buffer = 0;
        count = -1;
        offset = -1;
        q = 0;
    }
};

class IndexArrayPrivate
{
public:
};

class VertexArrayPrivate
{
public:
};

class BufferPrivate
{
public:
    QGLBuffer *buffer;
    int count; // item count (not byte count)

    QList<Array*> arrays;

    BufferPrivate(int count)
        :   buffer(0)
        ,   count(count)
    {
    }

    ~BufferPrivate()
    {
        arrays.clear();

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

    void initArray(ArrayPrivate *array_d)
    {
        Array *array = array_d->q;
        Q_ASSERT(!arrays.contains(array));

        // Find space for array in buffer.
        if (arrays.isEmpty())
            arrays.append(array);
        else {
            array_d->offset = arrays.last()->end();
            int i = 1;
            for (;  i < arrays.count();  ++i) {
                if (array->end() < arrays.at(i)->offset())
                    break;
                array_d->offset = arrays.at(i)->end();
            }
            Q_ASSERT(array->end() < count);
            arrays.insert(i, array);
        }
    }

    void removeArray(ArrayPrivate *array_d)
    {
        arrays.removeOne(array_d->q);
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

Array::Array(int count, Buffer *buffer)
    :   QObject(buffer)
    ,   d(new ArrayPrivate(this, count, buffer))
{
    Q_CHECK_PTR(d);

    d->buffer->d->initArray(d);
}

Array::~Array()
{
    if (d->buffer->d)
        d->buffer->d->removeArray(d);

    delete d;  d = 0;
}

int Array::offset() const
{
    return d->offset;
}

int Array::count() const
{
    return d->count;
}

IndexArray::IndexArray(int count, IndexBuffer *indexBuffer)
    :   Array(count, indexBuffer)
    ,   d(new IndexArrayPrivate())
{
    Q_CHECK_PTR(d);
}

IndexArray::~IndexArray()
{
    delete d;  d = 0;
}

void IndexArray::write(const QVector<index> &indices)
{
    QGLBuffer *buffer = Array::d->buffer->d->buffer;
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

VertexArray::VertexArray(int count, VertexBuffer *vertexBuffer)
    :   Array(count, vertexBuffer)
    ,   d(new VertexArrayPrivate())
{
    Q_CHECK_PTR(d);
}

VertexArray::~VertexArray()
{
    delete d;  d = 0;
}

void VertexArray::write(const QVector<Vertex> &vertices)
{
    QGLBuffer *buffer = Array::d->buffer->d->buffer;
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
