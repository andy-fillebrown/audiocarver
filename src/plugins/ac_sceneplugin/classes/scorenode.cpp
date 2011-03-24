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

#include "scorenode.h"

#include "fcurvenode.h"
#include "tracknode.h"

#include <ac_databaseplugin/classes/score.h>
#include <databaseplugin/classes/list.h>
#include <glsceneplugin/classes/buffer.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class ScoreNodePrivate
{
public:
    ScoreNode *q;
    Score *qdb;
    GL::IndexBuffer *ibo;
    GL::VertexBuffer *vbo;
    QList<TrackNode*> trackNodes;
    QList<FCurveNode*> curveNodes;
    QList<NoteNode*> noteNodes;

    ScoreNodePrivate(ScoreNode *q)
        :   q(q)
        ,   qdb(Score::instance())
        ,   ibo(new GL::IndexBuffer(1024000, q))
        ,   vbo(new GL::VertexBuffer(256000, q))
    {
        Q_ASSERT(qdb);
    }

    ~ScoreNodePrivate()
    {
        noteNodes.clear();
        curveNodes.clear();
        trackNodes.clear();

        vbo = 0;
        ibo = 0;
        qdb = 0;
        q = 0;
    }

    void updateCurves()
    {
        ac_updateNodeList_helper(curveNodes, qdb->curves()->data(), q);
    }

    void updateTracks()
    {
        ac_updateNodeList_helper(trackNodes, qdb->tracks()->data(), q);
    }
};

} // Internal
} // AudioCarver

ScoreNode::ScoreNode(QObject *parent)
    :   GL::Root(parent)
    ,   d(new ScoreNodePrivate(this))
{
    Q_CHECK_PTR(d);
}

ScoreNode::~ScoreNode()
{
    delete d;  d = 0;
}

void ScoreNode::appendNoteNode(NoteNode *noteNode)
{
    if (!d->noteNodes.contains(noteNode))
        d->noteNodes.append(noteNode);
}

void ScoreNode::removeNoteNode(NoteNode *noteNode)
{
    d->noteNodes.removeOne(noteNode);
}

void ScoreNode::updateProperty(int index)
{
    if (index == 0) {
        setObjectName(d->qdb->objectName());
        return;
    }

    const QString propertyName = d->qdb->propertyName(index);

    if (propertyName == "curves") {
        d->updateCurves();
        return;
    }

    if (propertyName == "tracks") {
        d->updateTracks();
        return;
    }
}
