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

#include "fcurvenode.h"

#include "notenode.h"
#include "scorenode.h"

#include <ac_databaseplugin/classes/fcurve.h>
#include <ac_databaseplugin/classes/note.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class FCurveNodePrivate
{
public:
    FCurveNode *q;
    FCurve *qdb;
    ScoreNode *scoreNode;
    QList<NoteNode*> noteNodes;

    FCurveNodePrivate(FCurveNode *q)
        :   q(q)
        ,   qdb(qobject_cast<FCurve*>(q->databaseObject()))
        ,   scoreNode(qobject_cast<ScoreNode*>(q->root()))
    {
        Q_ASSERT(qdb);
        Q_ASSERT(scoreNode);
    }

    ~FCurveNodePrivate()
    {
        noteNodes.clear();
        scoreNode = 0;
        qdb = 0;
        q = 0;
    }
};

} // Internal
} // AudioCarver

FCurveNode::FCurveNode(Database::Object *databaseObject, QObject *parent)
    :   Node(databaseObject, parent)
    ,   d(new FCurveNodePrivate(this))
{
    Q_CHECK_PTR(d);
}

FCurveNode::~FCurveNode()
{
    delete d;  d = 0;
}

void FCurveNode::appendNoteNode(NoteNode *noteNode)
{
    if (!d->noteNodes.contains(noteNode))
        d->noteNodes.append(noteNode);
}

void FCurveNode::removeNoteNode(NoteNode *noteNode)
{
    d->noteNodes.removeOne(noteNode);
    Q_ASSERT(!d->noteNodes.contains(noteNode));
}

void FCurveNode::updateProperty(int index)
{
    Node::updateProperty(index);
}
