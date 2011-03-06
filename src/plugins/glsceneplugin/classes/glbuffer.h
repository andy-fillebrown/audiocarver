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

#ifndef GLBUFFER_H
#define GLBUFFER_H

#include <QtCore/QObject>

#include <glsceneplugin/glscene_global.h>

#include <QtGui/QVector3D>

QT_BEGIN_NAMESPACE

class QGLBuffer;

QT_END_NAMESPACE

namespace GLScene {
namespace Internal {

class GLArrayPrivate;
class GLBufferPrivate;
class GLIndexArrayPrivate;
class GLIndexBufferPrivate;
class GLVertexArrayPrivate;
class GLVertexBufferPrivate;

} // namespace Internal

typedef quint16 GLIndex;

class GLVertex
{
public:
    float x;
    float y;
    float z;
    float pad;

    GLVertex(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z), pad(0.0f) {}
};

class GLSCENE_EXPORT GLBuffer : public QObject
{
    Q_OBJECT

public:
    GLBuffer(int count, QObject *parent = 0);
    virtual ~GLBuffer();

    int count() const;

    bool bind();
    void release();

private:
    friend class GLArray;
    friend class GLIndexArray;
    friend class GLIndexBuffer;
    friend class GLVertexArray;
    friend class GLVertexBuffer;
    Internal::GLBufferPrivate *d;
};

class GLSCENE_EXPORT GLIndexBuffer : public GLBuffer
{
    Q_OBJECT

public:
    GLIndexBuffer(int count, QObject *parent = 0);
    virtual ~GLIndexBuffer();

private:
    friend class GLIndexArray;
    Internal::GLIndexBufferPrivate *d;
};

class GLSCENE_EXPORT GLVertexBuffer : public GLBuffer
{
    Q_OBJECT

public:
    GLVertexBuffer(int count, QObject *parent = 0);
    virtual ~GLVertexBuffer();

private:
    friend class GLVertexArray;
    Internal::GLVertexBufferPrivate *d;
};

class GLSCENE_EXPORT GLArray : public QObject
{
    Q_OBJECT

protected:
    GLArray(int count, GLBuffer *buffer);
    virtual ~GLArray();

public:
    int offset() const;
    int count() const;
    int end() const { return offset() + count(); }

private:
    friend class GLIndexArray;
    friend class GLVertexArray;
    Internal::GLArrayPrivate *d;
};

class GLSCENE_EXPORT GLIndexArray : public GLArray
{
    Q_OBJECT

public:
    GLIndexArray(int count, GLIndexBuffer *indexBuffer);
    virtual ~GLIndexArray();

    void write(const QVector<GLIndex> &indices);

private:
    Internal::GLIndexArrayPrivate *d;
};

class GLSCENE_EXPORT GLVertexArray : public GLArray
{
    Q_OBJECT

public:
    GLVertexArray(int count, GLVertexBuffer *vertexBuffer);
    virtual ~GLVertexArray();

    void write(const QVector<GLVertex> &vertices);

private:
    Internal::GLVertexArrayPrivate *d;
};

} // namespace GLScene

#endif // GLBUFFER_H
