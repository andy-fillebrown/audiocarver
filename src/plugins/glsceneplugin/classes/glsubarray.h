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

#ifndef GLSUBARRAY_H
#define GLSUBARRAY_H

#include "glbuffer.h"

namespace GLScene {

class GLObject;

class GLSubArray : public QObject
{
    Q_OBJECT

public:
    GLSubArray(GLBuffer *buffer, quint32 count);
    virtual ~GLSubArray();

    int id() const;
    void setId(int id);

    int startOffset() const;
    void setStartOffset(int offset);

    int endOffset() const;

public slots:
    virtual void appendObject(GLObject *object);
    virtual void removeObject(GLObject *object);

signals:
    void idChanged(int from, int to);
};

class GLIndexSubArray : public GLSubArray
{
    Q_OBJECT

public:
    GLIndexSubArray(GLBuffer *buffer, quint32 count);
    virtual ~GLIndexSubArray();

    void write(const QVector<quint32> &indices);
};

class GLVertexSubArray : public GLSubArray
{
    Q_OBJECT

public:
    GLVertexSubArray(GLBuffer *buffer, quint32 count);
    virtual ~GLVertexSubArray();

    void write(const QVector<GLVertex> &vertices);
};

} // namespace GLScene

#endif // GLSUBARRAY_H
