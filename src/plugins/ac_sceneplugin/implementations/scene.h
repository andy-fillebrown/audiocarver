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

#ifndef AC_SCENE_H
#define AC_SCENE_H

#include <sceneplugin/interfaces/iscene.h>

namespace AudioCarver {
namespace Internal {

class SceneImplPrivate;

class SceneImpl : public Scene::IScene
{
public:
    SceneImpl();
    virtual ~SceneImpl();

private:
    SceneImplPrivate *d;
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_SCENE_H
