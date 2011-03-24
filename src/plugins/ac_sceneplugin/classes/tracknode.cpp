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

#include "tracknode.h"

#include "notenode.h"
#include "scorenode.h"

#include <ac_databaseplugin/classes/track.h>
#include <glsceneplugin/classes/buffer.h>
#include <databaseplugin/classes/object.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class TrackNodePrivate
{
public:
    TrackNode *q;
    Track *qdb;
    ScoreNode *scoreNode;
    GL::IndexBuffer *ibo;
    GL::VertexBuffer *vbo;
    QList<NoteNode*> noteNodes;

    TrackNodePrivate(TrackNode *q)
        :   q(q)
        ,   qdb(qobject_cast<Track*>(q->databaseObject()))
        ,   scoreNode(qobject_cast<ScoreNode*>(q->parent()))
        ,   ibo(new GL::IndexBuffer(1024000, q))
        ,   vbo(new GL::VertexBuffer(256000, q))
    {
        Q_ASSERT(qdb);
        Q_ASSERT(scoreNode);
        Q_CHECK_PTR(ibo);
        Q_CHECK_PTR(vbo);
    }

    ~TrackNodePrivate()
    {
        noteNodes.clear();

        vbo = 0;
        ibo = 0;
        scoreNode = 0;
        qdb = 0;
        q = 0;
    }

    void updateNoteNodes()
    {
        QList<NoteNode*> oldNoteNodes = noteNodes;
        QList<NoteNode*> removedNoteNodes = ac_updateNodeList_helper(noteNodes, qdb->notes()->data(), q);

        bool notesNodesAdded = false;

        foreach (NoteNode *noteNode, noteNodes) {
            if (!oldNoteNodes.contains(noteNode)) {
                scoreNode->appendNoteNode(noteNode);
                notesNodesAdded = true;
            }
        }
    }
};

} // namespace Internal
} // namespace AudioCarver

TrackNode::TrackNode(Database::Object *databaseObject, QObject *parent)
    :   Node(databaseObject, parent)
    ,   d(new TrackNodePrivate(this))
{
    Q_CHECK_PTR(d);
}

TrackNode::~TrackNode()
{
    delete d;  d = 0;
}

GL::IndexBuffer *TrackNode::indexBuffer() const
{
    return d->ibo;
}

GL::VertexBuffer *TrackNode::vertexBuffer() const
{
    return d->vbo;
}

void TrackNode::updateProperty(int index)
{
    const QString propertyName = databaseObject()->propertyName(index);

    if (propertyName == "notes") {
        d->updateNoteNodes();
        return;
    }

    Node::updateProperty(index);
}
