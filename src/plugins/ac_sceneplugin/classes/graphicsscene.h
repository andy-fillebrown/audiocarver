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

#ifndef AC_GRAPHICSSCENE_H
#define AC_GRAPHICSSCENE_H

#include <sceneplugin/classes/graphicsscene.h>

#include <ac_sceneplugin/ac_scene_global.h>

namespace AudioCarver {

class AC_SCENE_EXPORT GraphicsScene : public Scene::GraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject *parent = 0);
protected:
    virtual ~GraphicsScene() {}
private:
    Q_DISABLE_COPY(GraphicsScene)
};

} // namespace AudioCarver

#endif // AC_GRAPHICSSCENE_H
