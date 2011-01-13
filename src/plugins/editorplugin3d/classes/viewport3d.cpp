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

#include "viewport3d.h"

#include <utils/utils_global.h>

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

using namespace Editor3D;

Viewport3D::Viewport3D(QWidget *parent)
    :   QGLWidget(parent)
    ,   _framebufferObjectDisplayListId(0)
    ,   _fullscreenDisplayListId(0)
    ,   _framebufferObject(0)
    ,   _vertexShader(0)
    ,   _fragmentShader(0)
    ,   _shaderProgram(0)
{
}

Viewport3D::~Viewport3D()
{
    delete _framebufferObject; _framebufferObject = 0;
    _shaderProgram = 0;
    _fragmentShader = 0;
    _vertexShader = 0;
    glDeleteLists(_fullscreenDisplayListId, 1); _fullscreenDisplayListId = 0;
    glDeleteLists(_framebufferObjectDisplayListId, 1); _framebufferObjectDisplayListId = 0;
}

void Viewport3D::initializeGL()
{
    initializeFramebufferObject();
    initializeFullscreenShaderProgram();
}

void Viewport3D::paintGL()
{
    drawFullscreen();
}

void Viewport3D::initializeFramebufferObject()
{
    _framebufferObject = new QGLFramebufferObject(512, 512);
    initializeFramebufferObjectDisplayList();
    drawFramebufferObject();
}

void Viewport3D::initializeFramebufferObjectDisplayList()
{
    static const GLfloat rotationX =  0;
    static const GLfloat rotationY = 45;
    static const GLfloat rotationZ =  0;

    static const GLfloat P1[3] = { 0.0, -1.0, 2.0 };
    static const GLfloat P2[3] = { 1.73205081, -1.0, -1.0 };
    static const GLfloat P3[3] = { -1.73205081, -1.0, -1.0 };
    static const GLfloat P4[3] = { 0.0, +2.0, +0.0 };

    static const GLfloat * const coords[4][3] = {
        { P1, P2, P3 }, { P1, P3, P4 }, { P1, P4, P2 }, { P2, P4, P3 }
    };
    static const QColor faceColors[] = {
        Qt::red, Qt::green, Qt::blue, Qt::yellow
    };

    _framebufferObjectDisplayListId = glGenLists(1);
    glNewList(_framebufferObjectDisplayListId, GL_COMPILE);

    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 4; ++i) {
        qglColor(faceColors[i]);
        for (int j = 0; j < 3; ++j)
            glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
    }
    glEnd();

    glEndList();
}

void Viewport3D::drawFramebufferObject()
{
    bool ok = true;

    Q_CHECK(_framebufferObject->bind());

    saveGLState();

    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat x = GLfloat(512) / 512;
    glViewport(0, 0, 512, 512);
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);

    glCallList(_framebufferObjectDisplayListId);

    restoreGLState();

    Q_CHECK(ok = _framebufferObject->release());
}

void Viewport3D::initializeFullscreenShaderProgram()
{
    bool ok = true;

    const QString vs =
            "void main(void)\n"
            "{\n"
            "   gl_Position = gl_Vertex;\n"
            "}";
    const QString fs =
            "uniform sampler2D Texture;\n"
            "void main(void)\n"
            "{\n"
            "   gl_FragColor = texture2D(Texture, gl_FragCoord.xy / vec2(1024, 512));\n"
            "}";

    _vertexShader = new QGLShader(QGLShader::Vertex, this);
    Q_CHECK(ok = _vertexShader->compileSourceCode(vs));
    if (!ok)
        qDebug() << _vertexShader->log();

    _fragmentShader = new QGLShader(QGLShader::Fragment, this);
    Q_CHECK(ok = _fragmentShader->compileSourceCode(fs));
    if (!ok)
        qDebug() << _fragmentShader->log();

    _shaderProgram = new QGLShaderProgram(this);
    Q_CHECK(ok = _shaderProgram->addShader(_vertexShader));
    Q_CHECK(ok = _shaderProgram->addShader(_fragmentShader));
    Q_CHECK(ok = _shaderProgram->link());

    initializeFullscreenDisplayList();
}

void Viewport3D::initializeFullscreenDisplayList()
{
    _fullscreenDisplayListId = glGenLists(1);
    glNewList(_fullscreenDisplayListId, GL_COMPILE);

    glBegin(GL_TRIANGLES);
    glVertex2f(-2.0, -1.0);
    glVertex2f(2.0, -1.0);
    glVertex2f(0.0, 4.0);
    glEnd();

    glEndList();
}

void Viewport3D::drawFullscreen()
{
    bool ok = true;

    saveGLState();

    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width(), height());

    Q_CHECK(ok = _shaderProgram->bind());

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _framebufferObject->texture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glCallList(_fullscreenDisplayListId);

    restoreGLState();
}

void Viewport3D::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void Viewport3D::restoreGLState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}