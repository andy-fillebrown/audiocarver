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

#include <utils3d/utils3d_global.h>

#include <glsceneplugin/glscene_global.h>

QT_BEGIN_NAMESPACE

class QGLBuffer;

QT_END_NAMESPACE

namespace GL {
namespace Internal {

class ArrayPrivate;
class BufferPrivate;
class IndexArrayPrivate;
class IndexBufferPrivate;
class VertexArrayPrivate;
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
    friend class Array;
    friend class IndexArray;
    friend class IndexBuffer;
    friend class VertexArray;
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
    friend class IndexArray;
    Internal::IndexBufferPrivate *d;
};

class GLSCENE_EXPORT VertexBuffer : public Buffer
{
    Q_OBJECT

public:
    VertexBuffer(int count, QObject *parent = 0);
    virtual ~VertexBuffer();

private:
    friend class VertexArray;
    Internal::VertexBufferPrivate *d;
};

class GLSCENE_EXPORT Array : public QObject
{
    Q_OBJECT

protected:
    Array(int count, Buffer *buffer);
    virtual ~Array();

public:
    int offset() const;
    int count() const;
    int end() const { return offset() + count(); }

private:
    friend class IndexArray;
    friend class VertexArray;
    Internal::ArrayPrivate *d;
};

class GLSCENE_EXPORT IndexArray : public Array
{
    Q_OBJECT

public:
    IndexArray(int count, IndexBuffer *indexBuffer);
    virtual ~IndexArray();

    void write(const QVector<index> &indices);

private:
    Internal::IndexArrayPrivate *d;
};

class GLSCENE_EXPORT VertexArray : public Array
{
    Q_OBJECT

public:
    VertexArray(int count, VertexBuffer *vertexBuffer);
    virtual ~VertexArray();

    void write(const QVector<Vertex> &vertices);

private:
    Internal::VertexArrayPrivate *d;
};

} // namespace GL

#endif // GL_BUFFER_H
