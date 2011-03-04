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

#ifndef AC_SCORESCENE_H
#define AC_SCORESCENE_H

#include "sceneobject.h"

namespace AudioCarver {

class FCurveScene;
class NoteScene;

namespace Internal {
class ScoreScenePrivate;
} // Internal

class ScoreScene : public SceneObject
{
    Q_OBJECT

public:
    ScoreScene(QObject *parent = 0);
    virtual ~ScoreScene();

    int createVBOSubArray(int count);
    int createVBOSubArray(NoteScene *note);
    void setVBOSubArray(int i, float *data);
    void removeVBOSubArray(int i);
    void bindVBO();
    void releaseVBO();

    int createIBOSubArray(int count);
    void setIBOSubArray(int i, quint32 *data);
    void removeIBOSubArray(int i);
    void bindIBO();
    void releaseIBO();

    void appendNote(NoteScene *note);
    void removeNote(NoteScene *note);

protected:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(ScoreScene)
    Internal::ScoreScenePrivate *d;
};

} // namespace AudioCarver

#endif // AC_SCORESCENE_H
