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

#ifndef AC_NOTESCENE_H
#define AC_NOTESCENE_H

#include "sceneobject.h"

namespace AudioCarver {

class NoteScene : public SceneObject
{
    Q_OBJECT

public:
    NoteScene(Database::Object *databaseObject, QObject *parent = 0);
    virtual ~NoteScene();
};

} // namespace AudioCarver

#endif // AC_NOTESCENE_H
