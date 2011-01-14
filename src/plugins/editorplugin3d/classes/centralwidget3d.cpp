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

#include "centralwidget3d.h"
#include "viewport3d.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

using namespace Editor3D;

CentralWidget3D::CentralWidget3D(QWidget *parent)
    :   QGLWidget(parent)
    ,   _viewport(0)
    ,   _fullscreenDisplayListId(0)
    ,   _vertexShader(0)
    ,   _fragmentShader(0)
    ,   _shaderProgram(0)
    ,   _shaderProgramScreenSizeVariableId(-1)
{
}

CentralWidget3D::~CentralWidget3D()
{
    makeCurrent();

    _shaderProgramScreenSizeVariableId = -1;
    _shaderProgram = 0;
    _fragmentShader = 0;
    _vertexShader = 0;
    glDeleteLists(_fullscreenDisplayListId, 1);  _fullscreenDisplayListId = 0;
    delete _viewport;  _viewport = 0;
}

void CentralWidget3D::initializeGL()
{
    _viewport = new Viewport3D(this, size());

    initializeFullscreenShaderProgram();

    Q_CHECK_GLERROR;
}

void CentralWidget3D::paintGL()
{
    drawFullscreen();

    Q_CHECK_GLERROR;
}

void CentralWidget3D::resizeGL(int w, int h)
{
    _viewport->resize(w, h);

    Q_CHECK_GLERROR;
}

void CentralWidget3D::initializeFullscreenShaderProgram()
{
    const QString vs =
            "void main(void)\n"
            "{\n"
            "   gl_Position = gl_Vertex;\n"
            "}";
    const QString fs =
            "uniform sampler2D Texture;\n"
            "uniform vec2 screenSize;\n"
            "void main(void)\n"
            "{\n"
            "   gl_FragColor = texture2D(Texture, gl_FragCoord.xy / screenSize);\n"
            "}";
    _vertexShader = new QGLShader(QGLShader::Vertex, this);
    Q_CHECK(_vertexShader->compileSourceCode(vs));
    if (!_vertexShader->isCompiled())
        qDebug() << _vertexShader->log();
    _fragmentShader = new QGLShader(QGLShader::Fragment, this);
    Q_CHECK(_fragmentShader->compileSourceCode(fs));
    if (!_fragmentShader->isCompiled())
        qDebug() << _fragmentShader->log();
    _shaderProgram = new QGLShaderProgram(this);
    Q_CHECK(_shaderProgram->addShader(_vertexShader));
    Q_CHECK(_shaderProgram->addShader(_fragmentShader));
    Q_CHECK(_shaderProgram->link());
    _shaderProgramScreenSizeVariableId = _shaderProgram->uniformLocation("screenSize");
    Q_ASSERT(_shaderProgramScreenSizeVariableId != -1);
    initializeFullscreenDisplayList();

    Q_CHECK_GLERROR;
}

void CentralWidget3D::initializeFullscreenDisplayList()
{
    _fullscreenDisplayListId = glGenLists(1);
    glNewList(_fullscreenDisplayListId, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glVertex2f(-2.0, -1.0);
    glVertex2f(2.0, -1.0);
    glVertex2f(0.0, 4.0);
    glEnd();
    glEndList();

    Q_CHECK_GLERROR;
}

void CentralWidget3D::drawFullscreen()
{
    const int w = width();
    const int h = height();

    qglPushState();
    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, w, h);
    bindShaderProgram(w, h);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _viewport->textureId());
    glCallList(_fullscreenDisplayListId);
    releaseShaderProgram();
    qglPopState();

    Q_CHECK_GLERROR;
}

void CentralWidget3D::bindShaderProgram(int w, int h)
{
    Q_CHECK(_shaderProgram->bind());
    _shaderProgram->setUniformValue(_shaderProgramScreenSizeVariableId, w, h);

    Q_CHECK_GLERROR;
}

void CentralWidget3D::releaseShaderProgram()
{
    _shaderProgram->release();

    Q_CHECK_GLERROR;
}
