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

#ifndef AC_CONTROLLERSCENE_H
#define AC_CONTROLLERSCENE_H

#include <ac_graphicsscene.h>
#include <ac_scene_global.h>

namespace Private {

class AcControllerSceneData;

} // namespace Private

class AC_SCENE_EXPORT AcControllerScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcControllerScene(QObject *parent = 0);
    virtual ~AcControllerScene();
private:
    Q_DISABLE_COPY(AcControllerScene)
    Private::AcControllerSceneData *d;
};

#endif // AC_CONTROLLERSCENE_H
