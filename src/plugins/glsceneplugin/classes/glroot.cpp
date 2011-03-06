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

#include "glroot.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLBuffer>

using namespace GLScene;
using namespace GLScene::Internal;

namespace GLScene {
namespace Internal {

class GLRootPrivate
{
public:
    GLRoot *q;

    GLRootPrivate(GLRoot *q)
        :   q(q)
    {
    }

    ~GLRootPrivate()
    {
        q = 0;
    }
};

} // namespace Internal
} // namespace GLScene

GLRoot::GLRoot(QObject *parent)
    :   GLNode(parent)
    ,   d(new GLRootPrivate(this))
{
    Q_CHECK_PTR(d);
}

GLRoot::~GLRoot()
{
    delete d;  d = 0;
}

void GLRoot::drawLines(bool picking)
{
}

void GLRoot::drawTriangles(bool picking)
{
}

void GLRoot::releaseBuffers() const
{
    QGLBuffer::release(QGLBuffer::IndexBuffer);
    QGLBuffer::release(QGLBuffer::VertexBuffer);
    Q_CHECK_GLERROR;
}
