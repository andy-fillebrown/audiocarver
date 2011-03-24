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

#ifndef AC_SCORENODE_H
#define AC_SCORENODE_H

#include <glsceneplugin/classes/root.h>

namespace AudioCarver {

class NoteNode;

namespace Internal {
class ScoreNodePrivate;
} // Internal

class ScoreNode : public GL::Root
{
    Q_OBJECT

public:
    ScoreNode(QObject *parent = 0);
    virtual ~ScoreNode();

    void appendNoteNode(NoteNode *noteNode);
    void removeNoteNode(NoteNode *noteNode);

public slots:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(ScoreNode)
    Internal::ScoreNodePrivate *d;
};

} // namespace AudioCarver

#endif // AC_SCORENODE_H
