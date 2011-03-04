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

#include <QtOpenGL/QGLBuffer>

namespace GLScene {

class GLIndexSubArray;
class GLVertexSubArray;

class GLBuffer : public QObject
{
    Q_OBJECT

public:
    GLBuffer(QGLBuffer::Type bufferType, QObject *parent);
    virtual ~GLBuffer();

    bool bind();
    void release();

    int createSubArray(quint32 count);
    void destroySubArray(int i);

protected:
    void write(int offset, void *data, int byteCount);
};

class GLIndexBuffer : public GLBuffer
{
    Q_OBJECT

public:
    GLIndexBuffer(QObject *parent);
    virtual ~GLIndexBuffer();

    GLIndexSubArray *subArrayAt(int i);

    void write(int offset, const QVector<quint32> &indices);
};

typedef QVector3D GLVertex;

class GLVertexBuffer : public GLBuffer
{
    Q_OBJECT

public:
    GLVertexBuffer(QObject *parent);
    virtual ~GLVertexBuffer();

    GLVertexSubArray *subArrayAt(int i);

    void write(int offset, const QVector<GLVertex> &vertices);
};

} // namespace GLScene

#endif // GLBUFFER_H
