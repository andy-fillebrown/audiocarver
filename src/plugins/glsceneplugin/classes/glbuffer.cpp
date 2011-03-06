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

#include "glbuffer.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLBuffer>

using namespace GLScene;
using namespace GLScene::Internal;

namespace GLScene {
namespace Internal {

class GLArrayPrivate
{
public:
    GLArray *q;
    int offset;
    int count; // item count (not byte count)
    GLBuffer *buffer;

    GLArrayPrivate(GLArray *q, int count, GLBuffer *buffer)
        :   q(q)
        ,   offset(0) // set in GLBufferPrivate::initializeArray
        ,   count(count)
        ,   buffer(buffer)
    {
    }

    ~GLArrayPrivate()
    {
        buffer = 0;
        count = -1;
        offset = -1;
        q = 0;
    }
};

class GLIndexArrayPrivate
{
public:
};

class GLVertexArrayPrivate
{
public:
};

class GLBufferPrivate
{
public:
    QGLBuffer *buffer;
    int count; // item count (not byte count)

    QList<GLArray*> arrays;

    GLBufferPrivate(int count)
        :   buffer(0)
        ,   count(count)
    {
    }

    ~GLBufferPrivate()
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

        return buffer->type() == QGLBuffer::IndexBuffer ? sizeof(GLIndex) : sizeof(GLVertex);
    }

    void initializeBuffer(QGLBuffer::Type type)
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

    void initializeArray(GLArrayPrivate *array_d)
    {
        GLArray *array = array_d->q;
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

    void removeArray(GLArrayPrivate *array_d)
    {
        arrays.removeOne(array_d->q);
    }
};

class GLIndexBufferPrivate
{
public:
};

class GLVertexBufferPrivate
{
public:
};

} // namespace Internal
} // namespace GLScene

GLBuffer::GLBuffer(int count, QObject *parent)
    :   QObject(parent)
    ,   d(new GLBufferPrivate(count))
{
    Q_CHECK_PTR(d);
}

GLBuffer::~GLBuffer()
{
    delete d;  d = 0;
}

int GLBuffer::count() const
{
    return d->count;
}

bool GLBuffer::bind()
{
    return d->buffer->bind();
}

void GLBuffer::release()
{
    return d->buffer->release();
}

GLIndexBuffer::GLIndexBuffer(int count, QObject *parent)
    :   GLBuffer(count, parent)
    ,   d(new GLIndexBufferPrivate())
{
    Q_CHECK_PTR(d);

    GLBuffer::d->initializeBuffer(QGLBuffer::IndexBuffer);
}

GLIndexBuffer::~GLIndexBuffer()
{
    delete d;  d = 0;
}

GLVertexBuffer::GLVertexBuffer(int count, QObject *parent)
    :   GLBuffer(count, parent)
    ,   d(new GLVertexBufferPrivate())
{
    Q_CHECK_PTR(d);

    GLBuffer::d->initializeBuffer(QGLBuffer::VertexBuffer);
}

GLVertexBuffer::~GLVertexBuffer()
{
    delete d;  d = 0;
}

GLArray::GLArray(int count, GLBuffer *buffer)
    :   QObject(buffer)
    ,   d(new GLArrayPrivate(this, count, buffer))
{
    Q_CHECK_PTR(d);

    d->buffer->d->initializeArray(d);
}

GLArray::~GLArray()
{
    d->buffer->d->removeArray(d);

    delete d;  d = 0;
}

int GLArray::offset() const
{
    return d->offset;
}

int GLArray::count() const
{
    return d->count;
}

GLIndexArray::GLIndexArray(int count, GLIndexBuffer *indexBuffer)
    :   GLArray(count, indexBuffer)
    ,   d(new GLIndexArrayPrivate())
{
    Q_CHECK_PTR(d);
}

GLIndexArray::~GLIndexArray()
{
    delete d;  d = 0;
}

void GLIndexArray::write(const QVector<GLIndex> &indices)
{
    QGLBuffer *buffer = GLArray::d->buffer->d->buffer;
    Q_ASSERT(buffer);
    if (!buffer)
        return;

    bool ok = buffer->bind();
    Q_ASSERT(ok);
    Q_CHECK_GLERROR;
    if (!ok)
        return;

    buffer->write(offset() * sizeof(GLIndex),
                  indices.data(),
                  count() * sizeof(GLIndex));
}

GLVertexArray::GLVertexArray(int count, GLVertexBuffer *vertexBuffer)
    :   GLArray(count, vertexBuffer)
    ,   d(new GLVertexArrayPrivate())
{
    Q_CHECK_PTR(d);
}

GLVertexArray::~GLVertexArray()
{
    delete d;  d = 0;
}

void GLVertexArray::write(const QVector<GLVertex> &vertices)
{
    QGLBuffer *buffer = GLArray::d->buffer->d->buffer;
    Q_ASSERT(buffer);
    if (!buffer)
        return;

    bool ok = buffer->bind();
    Q_ASSERT(ok);
    Q_CHECK_GLERROR;
    if (!ok)
        return;

    buffer->write(offset() * sizeof(GLVertex),
                  vertices.data(),
                  count() * sizeof(GLVertex));
}
