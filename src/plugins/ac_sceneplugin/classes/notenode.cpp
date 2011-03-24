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

#include "notenode.h"

#include "fcurvenode.h"
#include "tracknode.h"

#include <ac_databaseplugin/classes/note.h>

#include <glsceneplugin/classes/root.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class NoteNodePrivate
{
public:
    NoteNode *q;
    Note *qdb;
    TrackNode *trackNode;
    FCurveNode *pitchCurveNode;
    FCurveNode *volumeCurveNode;
    int lineIndexBufferId;
    int polygonIndexBufferId;

    NoteNodePrivate(NoteNode *q)
        :   q(q)
        ,   qdb(qobject_cast<Note*>(q->databaseObject()))
        ,   trackNode(qobject_cast<TrackNode*>(q->parent()))
        ,   pitchCurveNode(trackNode->parent()->findChild<FCurveNode*>(qdb->pitchCurve()->id()))
        ,   volumeCurveNode(trackNode->parent()->findChild<FCurveNode*>(qdb->volumeCurve()->id()))
    {
        Q_ASSERT(qdb);
        Q_ASSERT(trackNode);

        if (pitchCurveNode)
            pitchCurveNode->appendNoteNode(q);

        if (volumeCurveNode)
            volumeCurveNode->appendNoteNode(q);
    }

    ~NoteNodePrivate()
    {
        volumeCurveNode = 0;
        pitchCurveNode = 0;
        trackNode = 0;
        qdb = 0;
        q = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

NoteNode::NoteNode(Database::Object *databaseObject, QObject *parent)
    :   Node(databaseObject, parent)
    ,   d(new NoteNodePrivate(this))
{
    Q_CHECK_PTR(d);
}

NoteNode::~NoteNode()
{
    delete d;  d = 0;
}

void NoteNode::updateProperty(int index)
{
    const QString propertyName = databaseObject()->propertyName(index);

    if (propertyName == "pointCount") {
        Q_ASSERT(false && "Not implemented yet");
        return;
    }

    if (propertyName == "pitchCurve") {
        if (d->pitchCurveNode)
            d->pitchCurveNode->removeNoteNode(this);
        d->pitchCurveNode = root()->findChild<FCurveNode*>(d->qdb->pitchCurve()->id());
        if (d->pitchCurveNode)
            d->pitchCurveNode->appendNoteNode(this);
        return;
    }

    if (propertyName == "volumeCurve") {
        if (d->volumeCurveNode)
            d->volumeCurveNode->removeNoteNode(this);
        d->volumeCurveNode = root()->findChild<FCurveNode*>(d->qdb->volumeCurve()->id());
        if (d->volumeCurveNode)
            d->volumeCurveNode->appendNoteNode(this);
        return;
    }

    Node::updateProperty(index);
}
