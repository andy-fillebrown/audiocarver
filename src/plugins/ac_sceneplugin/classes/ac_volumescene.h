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

#ifndef AC_VOLUMESCENE_H
#define AC_VOLUMESCENE_H

#include <ac_graphicsscene.h>

#include <ac_scene_global.h>

namespace Private {

class AcVolumeSceneData;

} // namespace Private

class AC_SCENE_EXPORT AcVolumeScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcVolumeScene(QObject *parent = 0);
    virtual ~AcVolumeScene();

protected:
    virtual void updateScoreProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcVolumeScene)
    Private::AcVolumeSceneData *d;
};

#endif // AC_VOLUMESCENE_H