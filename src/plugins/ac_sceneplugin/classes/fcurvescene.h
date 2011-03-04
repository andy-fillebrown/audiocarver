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

#ifndef AC_FCURVESCENE_H
#define AC_FCURVESCENE_H

#include "sceneobject.h"

namespace AudioCarver {

class NoteScene;

namespace Internal {
class FCurveScenePrivate;
} // Internal

class FCurveScene : public SceneObject
{
    Q_OBJECT

public:
    FCurveScene(Database::Object *databaseObject, QObject* parent);
    virtual ~FCurveScene();

    void appendNote(NoteScene *note);
    void removeNote(NoteScene *note);

    int maxPointCount() const;
    void setMaxPointCount(int count);

public slots:
    virtual void updateVBOs();

protected:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(FCurveScene)
    Internal::FCurveScenePrivate *d;
};

} // namespace AudioCarver

#endif // AC_FCURVESCENE_H
