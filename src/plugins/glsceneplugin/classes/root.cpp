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

#include "root.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLBuffer>

using namespace GL;
using namespace GL::Internal;

namespace GL {
namespace Internal {

class RootPrivate
{
public:
    Root *q;

    RootPrivate(Root *q)
        :   q(q)
    {
    }

    ~RootPrivate()
    {
        q = 0;
    }
};

} // namespace Internal
} // namespace GL

Root::Root(QObject *parent)
    :   Node(parent)
    ,   d(new RootPrivate(this))
{
    Q_CHECK_PTR(d);
}

Root::~Root()
{
    delete d;  d = 0;
}

void Root::drawLines(bool picking)
{
    Q_UNUSED(picking);
}

void Root::drawTriangles(bool picking)
{
    Q_UNUSED(picking);
}

void Root::releaseBuffers() const
{
    QGLBuffer::release(QGLBuffer::IndexBuffer);
    QGLBuffer::release(QGLBuffer::VertexBuffer);
    Q_CHECK_GLERROR;
}
