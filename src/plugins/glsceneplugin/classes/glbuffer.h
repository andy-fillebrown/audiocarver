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

#include <QtGui/QVector3D>

#include <QtOpenGL/QGLBuffer>

namespace GLScene {

typedef QVector3D GLVertex;

class GLIndexSubArray;
class GLVertexSubArray;

namespace Internal {

class GLBufferPrivate;
class GLIndexBufferPrivate;
class GLVertexBufferPrivate;

} // namespace Internal

class GLBuffer : public QObject
{
    Q_OBJECT

public:
    GLBuffer(QGLBuffer::Type bufferType, QObject *parent);
    virtual ~GLBuffer();

    bool bind();
    void release();

    virtual int createSubArray(int count) = 0;
    virtual void destroySubArray(int i) = 0;

    friend class GLIndexBuffer;
    friend class GLVertexBuffer;

private:
    Internal::GLBufferPrivate *d;
};

class GLIndexBuffer : public GLBuffer
{
    Q_OBJECT

public:
    GLIndexBuffer(QObject *parent);
    virtual ~GLIndexBuffer();

    virtual int createSubArray(int count);
    virtual void destroySubArray(int i);
    GLIndexSubArray *subArrayAt(int i);

protected:
    friend class GLIndexSubArray;

    void write(int offset, const QVector<quint32> &indices);

private:
    Internal::GLIndexBufferPrivate *d;
};

class GLVertexBuffer : public GLBuffer
{
    Q_OBJECT

public:
    GLVertexBuffer(QObject *parent);
    virtual ~GLVertexBuffer();

    virtual int createSubArray(int count);
    virtual void destroySubArray(int i);
    GLVertexSubArray *subArrayAt(int i);

protected:
    friend class GLVertexSubArray;

    void write(int offset, const QVector<GLVertex> &vertices);

private:
    Internal::GLVertexBufferPrivate *d;
};

} // namespace GLScene

#endif // GLBUFFER_H
