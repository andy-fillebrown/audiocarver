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

#ifndef GL_SCENE_H
#define GL_SCENE_H

#include <glsceneplugin/interfaces/iscene.h>

namespace GL {

class GLSCENE_EXPORT Scene : public IScene
{
    Q_OBJECT

public:
    Scene(QObject *parent = 0);
    virtual ~Scene();

    virtual void initialize() = 0;
    virtual void destroy() = 0;

    virtual bool drawBackground() { return false; }
    virtual bool drawStatic() { return false; }
    virtual bool drawModel() { return false; }
    virtual bool drawEdit() { return false; }
    virtual bool drawAnimation(qreal time) { Q_UNUSED(time);  return false; }
    virtual bool drawOverlay() { return false; }
};

} // namespace GL

#endif // GL_SCENE_H
