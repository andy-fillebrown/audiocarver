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

#include "glsubarray.h"

using namespace GLScene;

GLSubArray::GLSubArray(GLBuffer *buffer)
    :   QObject(buffer)
{
}

GLSubArray::~GLSubArray()
{
}

void GLSubArray::appendObject(GLObject *object)
{
}

void GLSubArray::removeObject(GLObject *object)
{
}

GLIndexSubArray::GLIndexSubArray(GLIndexBuffer *buffer, quint32 count)
    :   GLSubArray(buffer)
{
}

GLIndexSubArray::~GLIndexSubArray()
{
}

GLVertexSubArray::GLVertexSubArray(GLVertexBuffer *buffer, quint32 count)
    :   GLSubArray(buffer)
{
}

GLVertexSubArray::~GLVertexSubArray()
{
}
