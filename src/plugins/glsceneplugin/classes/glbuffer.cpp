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

#include "glsubarray.h"

using namespace GLScene;
using namespace GLScene::Internal;

namespace GLScene {
namespace Internal {

class GLBufferData
{
public:
    GLBuffer *q;
    QGLBuffer *qglbuffer;
    QList<GLSubArray*> subArrays;

    GLBufferData()
        :   q(0)
        ,   qglbuffer(0)
    {
    }
};

// Do not use.  Use quint32 or GLVertex to avoid compiler errors.
template <typename T> class GLBufferHelperBase {};

template <>
class GLBufferHelperBase<quint32> : public GLBufferData
{
public:
    typedef GLIndexSubArray SubArrayT;

    GLBufferHelperBase()
    {
        qglbuffer = new QGLBuffer(QGLBuffer::IndexBuffer);
    }

    GLSubArray *newSubArray(int count, quint32 dummy)
    {
        return new GLIndexSubArray(q, count);
    }
};

template <>
class GLBufferHelperBase<GLVertex> : public GLBufferData
{
public:
    typedef GLVertexSubArray SubArrayT;

    GLBufferHelperBase()
    {
        qglbuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    }

    GLSubArray *newSubArray(int count, GLVertex dummy)
    {
        return new GLVertexSubArray(q, count);
    }
};

template <typename T>
class GLBufferHelper : public GLBufferHelperBase<T>
{
    typedef GLBufferHelperBase<T> h;

public:
    GLBufferHelper(GLBuffer *q)
    {
        this->q = q;

        bool ok = h::qglbuffer->create();
        Q_ASSERT(ok);

        h::qglbuffer->setUsagePattern(QGLBuffer::StaticDraw);
        h::qglbuffer->allocate(1024000 * sizeof(T));

        ok = h::qglbuffer->bind();
        Q_ASSERT(ok);
    }

    ~GLBufferHelper()
    {
        h::qglbuffer->release();
        h::qglbuffer->destroy();
        delete h::qglbuffer;  h::qglbuffer = 0;
    }

    int createSubArray(int count)
    {
        GLSubArray *subArray = newSubArray(count, T());
        int startOffset = 0;

        if (!h::subArrays.isEmpty()) {

            // Search for unused area between sub-arrays large enough for count.
            startOffset = h::subArrays.first()->endOffset();

            for (int i = 1;  i < h::subArrays.count();  ++i) {
                if (count <= h::subArrays.at(i)->startOffset() - startOffset) {
                    subArray->setStartOffset(startOffset);
                    h::subArrays.insert(i, subArray);
                    return i;
                }
            }

            // No unused area found between sub-arrays.
            startOffset = h::subArrays.last()->endOffset();
        }

        subArray->setStartOffset(startOffset);
        h::subArrays.append(subArray);
        return h::subArrays.count() - 1;
    }
};

class GLBufferPrivate
{
public:
    QGLBuffer *buffer;
};

class GLIndexBufferPrivate
{
public:
    GLIndexBuffer *q;
    GLBufferHelper<quint32> bufferHelper;

    GLIndexBufferPrivate(GLIndexBuffer *q)
        :   q(q)
        ,   bufferHelper(q)
    {
    }

    ~GLIndexBufferPrivate()
    {
        q = 0;
    }
};

class GLVertexBufferPrivate
{
public:
    GLVertexBuffer *q;
    GLBufferHelper<GLVertex> bufferHelper;

    GLVertexBufferPrivate(GLVertexBuffer *q)
        :   q(q)
        ,   bufferHelper(q)
    {
    }

    ~GLVertexBufferPrivate()
    {
        q = 0;
    }
};

} // namespace Internal
} // namespace GLScene

GLBuffer::GLBuffer(QGLBuffer::Type bufferType, QObject *parent)
    :   QObject(parent)
    ,   d(new GLBufferPrivate)
{
}

GLBuffer::~GLBuffer()
{
    delete d;  d = 0;
}

bool GLBuffer::bind()
{
    return d->buffer->bind();
}

void GLBuffer::release()
{
    d->buffer->release();
}

GLIndexBuffer::GLIndexBuffer(QObject *parent)
    :   GLBuffer(QGLBuffer::IndexBuffer, parent)
    ,   d(new GLIndexBufferPrivate(this))
{
    GLBuffer::d->buffer = d->bufferHelper.qglbuffer;
}

GLIndexBuffer::~GLIndexBuffer()
{
    delete d;  d = 0;
}

int GLIndexBuffer::createSubArray(int count)
{
    return d->bufferHelper.createSubArray(count);
}

void GLIndexBuffer::destroySubArray(int i)
{
    GLSubArray *subArray = d->bufferHelper.subArrays.at(i);
    d->bufferHelper.subArrays.removeAt(i);
    delete subArray;
}

GLIndexSubArray *GLIndexBuffer::subArrayAt(int i)
{
    return qobject_cast<GLIndexSubArray*>(d->bufferHelper.subArrays[i]);
}

void GLIndexBuffer::write(int offset, const QVector<quint32> &indices)
{
    GLBuffer::d->buffer->write(offset, indices.data(), indices.count() * sizeof(quint32));
}

GLVertexBuffer::GLVertexBuffer(QObject *parent)
    :   GLBuffer(QGLBuffer::VertexBuffer, parent)
    ,   d(new GLVertexBufferPrivate(this))
{
    GLBuffer::d->buffer = d->bufferHelper.qglbuffer;
}

GLVertexBuffer::~GLVertexBuffer()
{
    delete d;  d = 0;
}

int GLVertexBuffer::createSubArray(int count)
{
    return d->bufferHelper.createSubArray(count);
}

void GLVertexBuffer::destroySubArray(int i)
{
    GLSubArray *subArray = d->bufferHelper.subArrays.at(i);
    d->bufferHelper.subArrays.removeAt(i);
    delete subArray;
}

GLVertexSubArray *GLVertexBuffer::subArrayAt(int i)
{
    return qobject_cast<GLVertexSubArray*>(d->bufferHelper.subArrays[i]);
}

void GLVertexBuffer::write(int offset, const QVector<GLVertex> &vertices)
{
    GLBuffer::d->buffer->write(offset, vertices.data(), vertices.count() * sizeof(GLVertex));
}
