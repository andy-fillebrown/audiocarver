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

#ifndef AC_TRACKSCENE_H
#define AC_TRACKSCENE_H

#include "sceneobject.h"

namespace AudioCarver {

class ScoreScene;

namespace Internal {
class TrackScenePrivate;
} // Internal

class TrackScene : public SceneObject
{
    Q_OBJECT

public:
    TrackScene(Database::Object *databaseObject, QObject *parent);
    virtual ~TrackScene();

protected:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(TrackScene)
    Internal::TrackScenePrivate *d;
};

} // namespace AudioCarver

#endif // AC_TRACKSCENE_H
