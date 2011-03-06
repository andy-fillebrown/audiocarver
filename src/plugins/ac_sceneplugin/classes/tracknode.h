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

#ifndef AC_TRACKNODE_H
#define AC_TRACKNODE_H

#include "node.h"

namespace GLScene {

class GLIndexBuffer;
class GLVertexBuffer;

} // namespace GLScene

namespace AudioCarver {
namespace Internal {

class TrackNodePrivate;

} // Internal

class TrackNode : public Node
{
    Q_OBJECT

public:
    TrackNode(Database::Object *databaseObject, QObject *parent);
    virtual ~TrackNode();

    GLScene::GLIndexBuffer *indexBuffer() const;
    GLScene::GLVertexBuffer *vertexBuffer() const;

protected:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(TrackNode)
    Internal::TrackNodePrivate *d;
};

} // namespace AudioCarver

#endif // AC_TRACKNODE_H
