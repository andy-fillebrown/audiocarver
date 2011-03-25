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

#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include <QtCore/QObject>

#include <glutils/glutils_global.h>

#include <glsceneplugin/glscene_global.h>

QT_BEGIN_NAMESPACE

class QGLBuffer;

QT_END_NAMESPACE

namespace GL {
namespace Internal {

class BufferPrivate;
class SubBufferPrivate;
class IndexSubBufferPrivate;
class IndexBufferPrivate;
class VertexSubBufferPrivate;
class VertexBufferPrivate;

} // namespace Internal

class Vertex
{
public:
    real x;
    real y;
    real z;
    real pad;

    Vertex(real x = 0.0f, real y = 0.0f, real z = 0.0f)
        :   x(x), y(y), z(z), pad(0.0f)
    {}
};

class GLSCENE_EXPORT Buffer : public QObject
{
    Q_OBJECT

public:
    Buffer(int count, QObject *parent = 0);
    virtual ~Buffer();

    int count() const;

    bool bind();
    void release();

private:
    friend class SubBuffer;
    friend class IndexSubBuffer;
    friend class IndexBuffer;
    friend class VertexSubBuffer;
    friend class VertexBuffer;
    Internal::BufferPrivate *d;
};

class GLSCENE_EXPORT IndexBuffer : public Buffer
{
    Q_OBJECT

public:
    IndexBuffer(int count, QObject *parent = 0);
    virtual ~IndexBuffer();

private:
    friend class IndexSubBuffer;
    Internal::IndexBufferPrivate *d;
};

class GLSCENE_EXPORT VertexBuffer : public Buffer
{
    Q_OBJECT

public:
    VertexBuffer(int count, QObject *parent = 0);
    virtual ~VertexBuffer();

private:
    friend class VertexSubBuffer;
    Internal::VertexBufferPrivate *d;
};

class GLSCENE_EXPORT SubBuffer : public QObject
{
    Q_OBJECT

protected:
    SubBuffer(int count, Buffer *buffer);
    virtual ~SubBuffer();

public:
    int offset() const;
    int count() const;
    int end() const { return offset() + count(); }

private:
    friend class IndexSubBuffer;
    friend class VertexSubBuffer;
    Internal::SubBufferPrivate *d;
};

class GLSCENE_EXPORT IndexSubBuffer : public SubBuffer
{
    Q_OBJECT

public:
    IndexSubBuffer(int count, IndexBuffer *indexBuffer);
    virtual ~IndexSubBuffer();

    void write(const QVector<index> &indices);

private:
    Internal::IndexSubBufferPrivate *d;
};

class GLSCENE_EXPORT VertexSubBuffer : public SubBuffer
{
    Q_OBJECT

public:
    VertexSubBuffer(int count, VertexBuffer *vertexBuffer);
    virtual ~VertexSubBuffer();

    void write(const QVector<Vertex> &vertices);

private:
    Internal::VertexSubBufferPrivate *d;
};

} // namespace GL

#endif // GL_BUFFER_H
