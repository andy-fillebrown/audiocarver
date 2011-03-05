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

#include "glnode.h"

namespace GLScene {

namespace Internal {

class GLSubArrayPrivate;
class GLIndexSubArrayPrivate;
class GLVertexSubArrayPrivate;

template <typename T>
class GLBufferHelperBase;

} // namespace Internal

class GLSCENE_EXPORT GLSubArray : public QObject
{
    Q_OBJECT

protected:
    GLSubArray(GLBuffer *buffer, int count);
    virtual ~GLSubArray();

    friend class GLIndexBuffer;
    friend class GLVertexBuffer;

public:
    int id() const;
    void setId(int id);

    int startOffset() const;
    void setStartOffset(int offset);

    int endOffset() const;

    const QList<GLNode*> &nodes() const;

    template <typename T>
    inline T findNode(const QString &name = QString()) const
    {
        foreach (GLNode *node, nodes()) {
            T t = qobject_cast<T>(node);
            if (t && (name.isEmpty() || t->objectName() == name))
                return t;
        }
        return 0;
    }

    template <typename T>
    inline QList<T> findNodes(const QString &name = QString()) const
    {
        QList<T> list;
        foreach (GLNode *node, nodes()) {
            T t = qobject_cast<T>(node);
            if (t && (name.isEmpty() || t->objectName() == name))
                list.append(t);
        }
        return list;
    }

public slots:
    virtual void appendNode(GLNode *node);
    virtual void removeNode(GLNode *node);

signals:
    void idChanged(int from, int to);

private:
    Q_DISABLE_COPY(GLSubArray)
    Internal::GLSubArrayPrivate *d;
};

class GLSCENE_EXPORT GLIndexSubArray : public GLSubArray
{
    Q_OBJECT

private:
    GLIndexSubArray(GLBuffer *buffer, int count);
    virtual ~GLIndexSubArray();

    template <typename T> friend class Internal::GLBufferHelperBase;

public:
    void write(const QVector<quint32> &indices);

private:
    Q_DISABLE_COPY(GLIndexSubArray)
    Internal::GLIndexSubArrayPrivate *d;
};

class GLSCENE_EXPORT GLVertexSubArray : public GLSubArray
{
    Q_OBJECT

private:
    GLVertexSubArray(GLBuffer *buffer, int count);
    virtual ~GLVertexSubArray();

    template <typename T> friend class Internal::GLBufferHelperBase;

public:
    void write(const QVector<GLVertex> &vertices);

private:
    Q_DISABLE_COPY(GLVertexSubArray)
    Internal::GLVertexSubArrayPrivate *d;
};

} // namespace GLScene

#endif // GLSUBARRAY_H

/*!
  \todo Figure out a better way of making the glbuffer.cpp classes the only
  classes that can create and delete sub-array objects, so the forward
  declarations of the internal GLBufferHelper template class and friend classes
  can be removed.
  */
