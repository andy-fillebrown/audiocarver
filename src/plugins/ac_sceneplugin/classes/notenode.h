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

#ifndef AC_NOTENODE_H
#define AC_NOTENODE_H

#include "node.h"

namespace AudioCarver {

namespace Internal {
class NoteNodePrivate;
} // namespace Internal;

class NoteNode : public Node
{
    Q_OBJECT

public:
    NoteNode(Database::Object *databaseObject, QObject *parent = 0);
    virtual ~NoteNode();

protected:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(NoteNode)
    Internal::NoteNodePrivate *d;
};

} // namespace AudioCarver

#endif // AC_NOTENODE_H
