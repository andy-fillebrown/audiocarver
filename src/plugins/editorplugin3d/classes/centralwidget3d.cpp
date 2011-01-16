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
    ,   _viewportLeft(0)
    ,   _viewportRight(0)
    ,   _fullscreenDisplayListId(0)
    ,   _vertexShader(0)
    ,   _fragmentShader(0)
    ,   _shaderProgram(0)
    ,   _shaderProgramScreenOriginVariableId(-1)
    ,   _shaderProgramScreenSizeVariableId(-1)
{
    startTimer(30);
}

CentralWidget3D::~CentralWidget3D()
{
    makeCurrent();

    _shaderProgramScreenSizeVariableId = -1;
    _shaderProgramScreenOriginVariableId = -1;
    _shaderProgram = 0;
    _fragmentShader = 0;
    _vertexShader = 0;
    glDeleteLists(_fullscreenDisplayListId, 1);  _fullscreenDisplayListId = 0;
    delete _viewportRight;  _viewportRight = 0;
    delete _viewportLeft;  _viewportLeft = 0;
}

void CentralWidget3D::initializeGL()
{
    const int w = width() / 2;
    const int h = height();

    _viewportLeft = new Viewport3D(this, w, h);
    _viewportLeft->setBackgroundColor(Qt::white);
    _viewportLeft->setRotation(2);

    _viewportRight = new Viewport3D(this, w, h);
    _viewportRight->setBackgroundColor(Qt::lightGray);
    _viewportRight->setRotation(3);

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
    w /= 2;
    _viewportLeft->resize(w, h);
    _viewportRight->resize(w, h);

    Q_CHECK_GLERROR;
}

void CentralWidget3D::timerEvent(QTimerEvent *event)
{
    updateGL();
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
            "uniform vec2 screenOrigin;\n"
            "uniform vec2 screenSize;\n"
            "void main(void)\n"
            "{\n"
            "   gl_FragColor = texture2D(Texture, (gl_FragCoord.xy - screenOrigin) / screenSize);\n"
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
    _shaderProgramScreenOriginVariableId = _shaderProgram->uniformLocation("screenOrigin");
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
    qglPushState();

    _viewportLeft->update();
    _viewportRight->update();

    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    Q_CHECK(_shaderProgram->bind());

    const QSize vpL = _viewportLeft->size();
    const int vpL_w = vpL.width();
    const int vpL_h = vpL.height();
    glViewport(0, 0, vpL.width(), vpL.height());
    _shaderProgram->setUniformValue(_shaderProgramScreenOriginVariableId, 0, 0);
    _shaderProgram->setUniformValue(_shaderProgramScreenSizeVariableId, vpL_w, vpL_h);
    glBindTexture(GL_TEXTURE_2D, _viewportLeft->textureId());
    glCallList(_fullscreenDisplayListId);

    const QSize vpR = _viewportRight->size();
    const int vpR_w = vpR.width();
    const int vpR_h = vpR.height();
    glViewport(vpL_w, 0, vpR_w, vpR_h);
    _shaderProgram->setUniformValue(_shaderProgramScreenOriginVariableId, vpL_w, 0);
    _shaderProgram->setUniformValue(_shaderProgramScreenSizeVariableId, vpR_w, vpR_h);
    glBindTexture(GL_TEXTURE_2D, _viewportRight->textureId());
    glCallList(_fullscreenDisplayListId);

    _shaderProgram->release();

    qglPopState();

    Q_CHECK_GLERROR;
}
