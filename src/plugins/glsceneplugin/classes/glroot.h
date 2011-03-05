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

#ifndef GLROOT_H
#define GLROOT_H

#include "glnode.h"

namespace GLScene {

class GLIndexBuffer;
class GLVertexBuffer;

namespace Internal {

class GLRootPrivate;

} // Internal

class GLRoot : public GLNode
{
    Q_OBJECT

public:
    GLRoot(QObject *parent = 0);
    virtual ~GLRoot();

    virtual bool isRoot() const { return true; }

    virtual void drawLines(bool picking = false);
    virtual void drawTriangles(bool picking = false);

    GLIndexBuffer *indexBuffer() const;
    GLVertexBuffer *vertexBuffer() const;

private:
    Q_DISABLE_COPY(GLRoot)
    Internal::GLRootPrivate *d;
};

} // namespace GLScene

#endif // GLROOT_H
