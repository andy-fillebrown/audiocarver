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

#ifndef GL_VIEWPORTSCENE_H
#define GL_VIEWPORTSCENE_H

#include <glsceneplugin/classes/scene.h>

namespace GL {

class Root;

namespace Internal {

class ViewportScenePrivate;

class ViewportScene : public Scene
{
public:
    ViewportScene(QObject *parent = 0);
    virtual ~ViewportScene();

    Root *rootNode() const;

    virtual void initialize();
    virtual void destroy();

    virtual bool drawStatic(bool picking = false);

private:
    ViewportScenePrivate *d;
};

} // namespace Internal
} // namespace GL

#endif // GL_VIEWPORTSCENE_H
