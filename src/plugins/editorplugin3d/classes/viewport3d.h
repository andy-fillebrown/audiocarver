/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef VIEWPORT3D_H
#define VIEWPORT3D_H

#include <editorplugin3d/editor3d_global.h>

#include <QtOpenGL/QGLWidget>

class QGLFramebufferObject;
class QImage;

namespace Editor3D {

class EDITOR3D_EXPORT Viewport3D : public QGLWidget
{
    Q_OBJECT

public:
    Viewport3D(QWidget *parent = 0);
    virtual ~Viewport3D();

protected:
    virtual void initializeGL();
    virtual void paintGL();

private:
    void draw();
    void saveGLState();
    void restoreGLState();

private:
    QGLFramebufferObject *_fbo;
};

} // namespace Editor3D

#endif // VIEWPORT3D_H
