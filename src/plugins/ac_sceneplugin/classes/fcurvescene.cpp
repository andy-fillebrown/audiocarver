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

#include "fcurvescene.h"

#include "scorescene.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class FCurveScenePrivate
{
public:
    ScoreScene *scoreScene;

    FCurveScenePrivate(ScoreScene *scoreScene)
        :   scoreScene(scoreScene)
    {
        Q_ASSERT(scoreScene);
    }

    ~FCurveScenePrivate()
    {
        scoreScene = 0;
    }
};

} // Internal
} // AudioCarver

FCurveScene::FCurveScene(Database::Object *databaseObject, QObject *parent)
    :   SceneObject(databaseObject, parent)
    ,   d(new FCurveScenePrivate(qobject_cast<ScoreScene*>(parent)))
{
    Q_CHECK_PTR(d);
}

FCurveScene::~FCurveScene()
{
    delete d;  d = 0;
}

void FCurveScene::updateProperty(int index)
{
    SceneObject::updateProperty(index);
}
