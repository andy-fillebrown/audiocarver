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

#ifndef CENTRALWIDGET3D_H
#define CENTRALWIDGET3D_H

#include <editorplugin3d/editor3d_global.h>

#include <QtOpenGL/QGLWidget>

QT_BEGIN_NAMESPACE

class QGLFramebufferObject;
class QGLShader;
class QGLShaderProgram;

QT_END_NAMESPACE

namespace Editor3D {

class Viewport3D;

class EDITOR3D_EXPORT CentralWidget3D : public QGLWidget
{
    Q_OBJECT

public:
    CentralWidget3D(const QGLFormat &format, QWidget *parent = 0);
    virtual ~CentralWidget3D();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void timerEvent(QTimerEvent *event);

private:
    void initializeFullscreenShaderProgram();
    void initializeFullscreenDisplayList();
    void drawFullscreen();

private:
    Viewport3D *_viewportLeft;
    Viewport3D *_viewportRight;
    GLuint _fullscreenDisplayListId;
    QGLShader *_vertexShader;
    QGLShader *_fragmentShader;
    QGLShaderProgram *_shaderProgram;
    int _shaderProgramScreenOriginVariableId;
    int _shaderProgramScreenSizeVariableId;
};

} // namespace Editor3D

#endif // CENTRALWIDGET3D_H
