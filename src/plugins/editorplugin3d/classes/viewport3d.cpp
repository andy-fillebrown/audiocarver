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
#include "centralwidget3d.h"

#include <utils3d/utils3d_global.h>

#include <QtCore/QTimerEvent>

#include <QtOpenGL/QGLFramebufferObject>

using namespace Editor3D;
using namespace Editor3D::Internal;

namespace Editor3D {
namespace Internal {

class Viewport3DPrivate : public QObject
{
public:
    Viewport3DPrivate(Viewport3D *q, CentralWidget3D *centralWidget, int w, int h);
    ~Viewport3DPrivate();

    Viewport3D *q;
    CentralWidget3D *centralWidget;
    QGLFramebufferObject *staticFBO;
    QGLFramebufferObject *animatedFBO;
    GLuint staticDisplayListId;
    GLuint animatedDisplayListId;
    int timerId;
    float rotation;
    float rotationDelta;
    QColor backgroundColor;
    bool dirtyStaticFBO;
    bool dirtyAnimatedFBO;

    void initFBOs(int w, int h);
    void initDisplayLists();
    void drawStaticFBO();
    void drawAnimatedFBO();
    void resize(int w, int h);

protected:
    virtual void timerEvent(QTimerEvent *event);
};

Viewport3DPrivate::Viewport3DPrivate(Viewport3D *q, CentralWidget3D *centralWidget, int w, int h)
    :   q(q)
    ,   centralWidget(centralWidget)
    ,   staticFBO(0)
    ,   animatedFBO(0)
    ,   staticDisplayListId(0)
    ,   animatedDisplayListId(0)
    ,   timerId(0)
    ,   rotation(0)
    ,   rotationDelta(0)
    ,   backgroundColor(Qt::white)
    ,   dirtyStaticFBO(true)
    ,   dirtyAnimatedFBO(true)
{
    initFBOs(w, h);
    initDisplayLists();
    drawStaticFBO();
    drawAnimatedFBO();

    timerId = startTimer(30);
}

Viewport3DPrivate::~Viewport3DPrivate()
{
    centralWidget->makeCurrent();

    dirtyAnimatedFBO = true;
    dirtyStaticFBO = true;
    backgroundColor = Qt::white;
    rotationDelta = 0;
    rotation = 0;
    timerId = 0;
    glDeleteLists(animatedDisplayListId, 1);  animatedDisplayListId = 0;
    glDeleteLists(staticDisplayListId, 1);  staticDisplayListId = 0;
    delete animatedFBO;  animatedFBO = 0;
    delete staticFBO;  staticFBO = 0;
    centralWidget = 0;
    q = 0;
}

void Viewport3DPrivate::initFBOs(int w, int h)
{
    centralWidget->makeCurrent();

    delete staticFBO;
    staticFBO = new QGLFramebufferObject(w, h);
    Q_ASSERT(staticFBO->isValid());

    delete animatedFBO;
    animatedFBO = new QGLFramebufferObject(w, h);
    Q_ASSERT(animatedFBO->isValid());
}

void Viewport3DPrivate::initDisplayLists()
{
    // animated fbo's display list
    static const GLfloat A1[3] = { 0.0, -1.0, 2.0 };
    static const GLfloat A2[3] = { 1.73205081, -1.0, -1.0 };
    static const GLfloat A3[3] = { -1.73205081, -1.0, -1.0 };
    static const GLfloat A4[3] = { 0.0, 2.0, 0.0 };
    static const GLfloat * const coordsA[4][3] = {
        { A1, A2, A3 }, { A1, A3, A4 }, { A1, A4, A2 }, { A2, A4, A3 }
    };
    static const GLfloat faceColorsA[][3] = {
        { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 1, 0 }
    };
    animatedDisplayListId = glGenLists(1);
    glNewList(animatedDisplayListId, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (int i = 0;  i < 4;  ++i) {
        glColor4f(faceColorsA[i][0], faceColorsA[i][1], faceColorsA[i][2], 0.5f);
        for (int j = 0; j < 3; ++j)
            glVertex3f(coordsA[i][j][0], coordsA[i][j][1], coordsA[i][j][2]);
    }
    glEnd();
    glEndList();
    Q_CHECK_GLERROR;

    // static fbo's display list
    static const GLfloat x = 1.0f;
    static const GLfloat y = 1.0f;
    static const GLfloat S1[3] = { x, y, 0.0 };
    static const GLfloat S2[3] = { x, -y, 0.0 };
    static const GLfloat S3[3] = { -x, y, 0.0 };
    static const GLfloat S4[3] = { -x, -y, 0.0 };
    static const GLfloat * const coordsS[2][3] = {
        { S2, S1, S3 }, { S3, S4, S2 }
    };
    staticDisplayListId = glGenLists(1);
    glNewList(staticDisplayListId, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glColor4f(0.5, 0.5, 0.5, 0.5);
    for (int i = 0;  i < 2;  ++i) {
        for (int j = 0;  j < 3;  ++j)
            glVertex3f(coordsS[i][j][0], coordsS[i][j][1], coordsS[i][j][2]);
    }
    glEnd();
    glEndList();
    Q_CHECK_GLERROR;
}

void Viewport3DPrivate::drawStaticFBO()
{
    const QSize size = staticFBO->size();
    const int w = size.width();
    const int h = size.height();
    const GLfloat aspect = w / GLfloat(h ? h : 1);

    centralWidget->makeCurrent();
    Q_CHECK(staticFBO->bind());

    glClearColor(0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
    glTranslatef(0.0, 0.0, -10.0);
    glCallList(staticDisplayListId);

    Q_CHECK(staticFBO->release());
    Q_CHECK_GLERROR;
    dirtyStaticFBO = false;
}

void Viewport3DPrivate::drawAnimatedFBO()
{
    const QSize size = animatedFBO->size();
    const int w = size.width();
    const int h = size.height();
    const GLfloat aspect = w / GLfloat(h ? h : 1);

    centralWidget->makeCurrent();

    Q_CHECK(animatedFBO->bind());

    glClearColor(1, 1, 1, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotation, 0.0, 1.0, 0.0);
    glCallList(animatedDisplayListId);

    Q_CHECK(animatedFBO->release());
    Q_CHECK_GLERROR;
    dirtyAnimatedFBO = false;
}

void Viewport3DPrivate::resize(int w, int h)
{
    initFBOs(w, h);
    dirtyStaticFBO = true;
    dirtyAnimatedFBO = true;
}

void Viewport3DPrivate::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != timerId)
        return;

    rotation += rotationDelta;
    dirtyAnimatedFBO = true;
}

} // namespace Internal
} // namespace Editor3D

Viewport3D::Viewport3D(CentralWidget3D *centralWidget, int w, int h)
    :   d(new Viewport3DPrivate(this, centralWidget, w, h))
{
}

Viewport3D::~Viewport3D()
{
    delete d;  d = 0;
}

CentralWidget3D *Viewport3D::centralWidget() const
{
    return d->centralWidget;
}

QSize Viewport3D::size() const
{
    return d->staticFBO->size();
}

void Viewport3D::setBackgroundColor(const QColor &color)
{
    d->backgroundColor = color;
}

void Viewport3D::setRotation(float rotation)
{
    d->rotationDelta = rotation;
}

GLuint Viewport3D::staticTextureId() const
{
    return d->staticFBO->texture();
}

GLuint Viewport3D::animatedTextureId() const
{
    return d->animatedFBO->texture();
}

void Viewport3D::update()
{
    if (d->dirtyAnimatedFBO)
        d->drawAnimatedFBO();

    if (d->dirtyStaticFBO)
        d->drawStaticFBO();
}

void Viewport3D::startCameraDrag(const QPoint &startPoint)
{
    Q_UNUSED(startPoint);
}

void Viewport3D::resize(int w, int h)
{
    d->resize(w, h);
}
