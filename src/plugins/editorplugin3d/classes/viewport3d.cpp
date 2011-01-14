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

#include <GL/glu.h> // gluErrorString

#define Q_CHECK(x) \
{ \
    bool ok = x; \
    Q_ASSERT(ok); \
}

#define Q_CHECK_GLERROR \
{ \
    GLenum e = glGetError(); \
    if (e != GL_NO_ERROR) \
        qDebug() << qPrintable( \
                QString("GL error in member function \'%1\'\n%2(%3): %4") \
                    .arg(Q_FUNC_INFO) \
                    .arg(__FILE__) \
                    .arg(__LINE__) \
                    .arg((char *)gluErrorString(e)) \
            ); \
    Q_ASSERT(e == GL_NO_ERROR); \
}

using namespace Editor3D;

Viewport3D::Viewport3D(QWidget *parent)
    :   QGLWidget(parent)
    ,   _framebufferObjectDisplayListId(0)
    ,   _fullscreenDisplayListId(0)
    ,   _framebufferObject(0)
    ,   _vertexShader(0)
    ,   _fragmentShader(0)
    ,   _shaderProgram(0)
    ,   _shaderProgramScreenSizeVariableId(-1)
    ,   _shaderProgramBound(false)
    ,   _timerId(0)
    ,   _rotationY(0)
{
    _timerId = startTimer(30);
}

Viewport3D::~Viewport3D()
{
    _shaderProgramBound = false;
    _shaderProgramScreenSizeVariableId = -1;
    _shaderProgram = 0;
    _fragmentShader = 0;
    _vertexShader = 0;
    delete _framebufferObject;
    _framebufferObject = 0;
    makeCurrent();
    glDeleteLists(_fullscreenDisplayListId, 1);
    _fullscreenDisplayListId = 0;
    glDeleteLists(_framebufferObjectDisplayListId, 1);
    _framebufferObjectDisplayListId = 0;
}

void Viewport3D::initializeGL()
{
    initializeFramebufferObject(width(), height());
    initializeFullscreenShaderProgram();
    Q_CHECK_GLERROR;
}

void Viewport3D::paintGL()
{
    drawFullscreen();
    Q_CHECK_GLERROR;
}

void Viewport3D::resizeGL(int w, int h)
{
    initializeFramebufferObject(w, h);
    Q_CHECK_GLERROR;
}

void Viewport3D::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != _timerId)
        return;
    _rotationY += 1;
    makeCurrent();
    drawFramebufferObject(width(), height());
    drawFullscreen();
    swapBuffers();
    Q_CHECK_GLERROR;
}

void Viewport3D::initializeFramebufferObject(int w, int h)
{
    delete _framebufferObject;
    _framebufferObject = new QGLFramebufferObject(w, h);
    initializeFramebufferObjectDisplayList();
    drawFramebufferObject(w, h);
    Q_CHECK_GLERROR;
}

void Viewport3D::initializeFramebufferObjectDisplayList()
{
    static const GLfloat P1[3] = { 0.0, -1.0, 2.0 };
    static const GLfloat P2[3] = { 1.73205081, -1.0, -1.0 };
    static const GLfloat P3[3] = { -1.73205081, -1.0, -1.0 };
    static const GLfloat P4[3] = { 0.0, 2.0, 0.0 };
    static const GLfloat * const coords[4][3] = {
        { P1, P2, P3 }, { P1, P3, P4 }, { P1, P4, P2 }, { P2, P4, P3 }
    };
    static const QColor faceColors[] = {
        Qt::red, Qt::green, Qt::blue, Qt::yellow
    };
    _framebufferObjectDisplayListId = glGenLists(1);
    glNewList(_framebufferObjectDisplayListId, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 4; ++i) {
        qglColor(faceColors[i]);
        for (int j = 0; j < 3; ++j)
            glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
    }
    glEnd();
    glEndList();
    Q_CHECK_GLERROR;
}

void Viewport3D::drawFramebufferObject(int w, int h)
{
    releaseShaderProgram();
    Q_CHECK(_framebufferObject->bind());
    saveGLState();
    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    // TODO: Fix frustum so view scales correctly when tall and skinny.
    GLfloat aspect = w / GLfloat(h ? h : 1);
    glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(_rotationY, 0.0, 1.0, 0.0);
    glCallList(_framebufferObjectDisplayListId);
    restoreGLState();
    Q_CHECK(_framebufferObject->release());
    Q_CHECK_GLERROR;
}

void Viewport3D::initializeFullscreenShaderProgram()
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
    Q_CHECK_GLERROR;
}

void Viewport3D::drawFullscreen()
{
    saveGLState();
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const int w = width();
    const int h = height();
    glViewport(0, 0, w, h);
    bindShaderProgram(w, h);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _framebufferObject->texture());
    glCallList(_fullscreenDisplayListId);
    restoreGLState();
    Q_CHECK_GLERROR;
}

void Viewport3D::bindShaderProgram(int w, int h)
{
    if (!_shaderProgramBound) {
        Q_CHECK(_shaderProgram->bind());
        _shaderProgram->setUniformValue(_shaderProgramScreenSizeVariableId, w, h);
        _shaderProgramBound = true;
        Q_CHECK_GLERROR;
    }
}

void Viewport3D::releaseShaderProgram()
{
    if (_shaderProgramBound) {
        _shaderProgram->release();
        _shaderProgramBound = false;
        Q_CHECK_GLERROR;
    }
}

void Viewport3D::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Q_CHECK_GLERROR;
}

void Viewport3D::restoreGLState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
    Q_CHECK_GLERROR;
}
