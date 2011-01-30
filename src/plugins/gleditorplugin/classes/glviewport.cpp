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

#include "glviewport.h"

#include "glwidget.h"
#include "glwidgetsplit.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLFunctions>

using namespace GLEditor;
using namespace GLEditor::Internal;

namespace GLEditor {
namespace Internal {

class GLViewportPrivate : protected QGLFunctions
{
public:
    GLViewport *q;
    GLWidget *widget;
    GLWidgetSplit *split;
    QColor backgroundColor;
    QGLFramebufferObject *staticFBO;
    QGLFramebufferObject *staticFBO_front;
    QGLFramebufferObject *staticFBO_back;
    QGLFramebufferObject *animatedFBO;
    QGLFramebufferObject *animatedFBO_front;
    QGLFramebufferObject *animatedFBO_back;
    QList<GLuint> textureIds;

    GLViewportPrivate(GLViewport *q, GLWidgetSplit *split, int w, int h)
        :   q(q)
        ,   widget(split->widget())
        ,   split(split)
        ,   backgroundColor(Qt::white)
        ,   staticFBO(0)
        ,   staticFBO_front(0)
        ,   staticFBO_back(0)
        ,   animatedFBO(0)
        ,   animatedFBO_front(0)
        ,   animatedFBO_back(0)
    {
        initializeGLFunctions(widget->context());
    }

    ~GLViewportPrivate()
    {
    }

    void initializeFBOs(int w, int h)
    {
    }

    void updateStaticFBO()
    {
    }

    void swapStaticBuffers()
    {
    }

    void updateAnimatedFBO()
    {
    }

    void swapAnimatedBuffers()
    {
    }

    void resize(int w, int h)
    {
    }
};

//Viewport3DPrivate::Viewport3DPrivate(Viewport3D *q, CentralWidget3D *centralWidget, int w, int h)
//    :   q(q)
//    ,   centralWidget(centralWidget)
//    ,   staticFBO(0)
//    ,   animatedFBO(0)
//    ,   staticDisplayListId(0)
//    ,   animatedDisplayListId(0)
//    ,   rotation(0)
//    ,   rotationPerFrame(0)
//    ,   backgroundColor(Qt::white)
//    ,   dirtyStaticFBO(true)
//{
//    initializeGLFunctions(centralWidget->context());

//    initFBOs(w, h);
//    initDisplayLists();
//    drawStaticFBO();
//    drawAnimatedFBO();
//}

//Viewport3DPrivate::~Viewport3DPrivate()
//{
//    centralWidget->makeCurrent();
//    Q_ASSERT(centralWidget->isValid());

//    dirtyStaticFBO = true;
//    backgroundColor = Qt::white;
//    rotationPerFrame = 0;
//    rotation = 0;
//    timerId = 0;
//    glDeleteLists(animatedDisplayListId, 1);  animatedDisplayListId = 0;
//    glDeleteLists(staticDisplayListId, 1);  staticDisplayListId = 0;
//    delete animatedFBO;  animatedFBO = 0;
//    delete staticFBO;  staticFBO = 0;
//    centralWidget = 0;
//    q = 0;
//}

//void Viewport3DPrivate::initFBOs(int w, int h)
//{
//    centralWidget->makeCurrent();
//    Q_ASSERT(centralWidget->isValid());

//    delete staticFBO;
//    staticFBO = new QGLFramebufferObject(w, h);
//    Q_ASSERT(staticFBO->isValid());

//    delete animatedFBO;
//    animatedFBO = new QGLFramebufferObject(w, h);
//    Q_ASSERT(animatedFBO->isValid());
//}

//void Viewport3DPrivate::initDisplayLists()
//{
//    // animated fbo's display list
//    static const GLfloat A1[3] = { 0.0, -1.0, 2.0 };
//    static const GLfloat A2[3] = { 1.73205081, -1.0, -1.0 };
//    static const GLfloat A3[3] = { -1.73205081, -1.0, -1.0 };
//    static const GLfloat A4[3] = { 0.0, 2.0, 0.0 };
//    static const GLfloat * const coordsA[4][3] = {
//        { A1, A2, A3 }, { A1, A3, A4 }, { A1, A4, A2 }, { A2, A4, A3 }
//    };
//    static const GLfloat faceColorsA[][3] = {
//        { 1, 1, 1 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }
//    };
//    animatedDisplayListId = glGenLists(1);
//    glNewList(animatedDisplayListId, GL_COMPILE);
//    glBegin(GL_TRIANGLES);
//    for (int i = 0;  i < 4;  ++i) {
//        glColor4f(faceColorsA[i][0], faceColorsA[i][1], faceColorsA[i][2], 0.5f);
//        for (int j = 0; j < 3; ++j)
//            glVertex3f(coordsA[i][j][0], coordsA[i][j][1], coordsA[i][j][2]);
//    }
//    glEnd();
//    glEndList();
//    Q_CHECK_GLERROR;

//    // static fbo's display list
//    static const GLfloat x = 1.0f;
//    static const GLfloat y = 1.0f;
//    static const GLfloat S1[3] = { x, y, 0.0 };
//    static const GLfloat S2[3] = { x, -y, 0.0 };
//    static const GLfloat S3[3] = { -x, y, 0.0 };
//    static const GLfloat S4[3] = { -x, -y, 0.0 };
//    static const GLfloat * const coordsS[2][3] = {
//        { S2, S1, S3 }, { S3, S4, S2 }
//    };
//    staticDisplayListId = glGenLists(1);
//    glNewList(staticDisplayListId, GL_COMPILE);
//    glBegin(GL_TRIANGLES);
//    glColor4f(0.5, 0.5, 0.5, 0.5);
//    for (int i = 0;  i < 2;  ++i) {
//        for (int j = 0;  j < 3;  ++j)
//            glVertex3f(coordsS[i][j][0], coordsS[i][j][1], coordsS[i][j][2]);
//    }
//    glEnd();
//    glEndList();
//    Q_CHECK_GLERROR;
//}

//void Viewport3DPrivate::drawStaticFBO()
//{
//    const QSize size = staticFBO->size();
//    const int w = size.width();
//    const int h = size.height();
//    const GLfloat aspect = w / GLfloat(h ? h : 1);

//    centralWidget->makeCurrent();
//    Q_ASSERT(centralWidget->isValid());
//    Q_CHECK(staticFBO->bind());

//    glClearColor(0, 0, 0, 0.5);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glDisable(GL_ALPHA_TEST);
//    glShadeModel(GL_FLAT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glViewport(0, 0, w, h);
//    glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
//    glTranslatef(0.0, 0.0, -10.0);
//    glCallList(staticDisplayListId);

//    Q_CHECK(staticFBO->release());
//    Q_CHECK_GLERROR;
//    dirtyStaticFBO = false;
//}

//void Viewport3DPrivate::drawAnimatedFBO()
//{
//    const QSize size = animatedFBO->size();
//    const int w = size.width();
//    const int h = size.height();
//    const GLfloat aspect = w / GLfloat(h ? h : 1);

//    centralWidget->makeCurrent();
//    Q_ASSERT(centralWidget->isValid());
//    Q_CHECK(animatedFBO->bind());

//    glClearColor(1, 1, 1, 0.5);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFuncSeparate(GL_SRC_ALPHA, GL_DST_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);
//    glShadeModel(GL_FLAT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glViewport(0, 0, w, h);
//    glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
//    glTranslatef(0.0, 0.0, -10.0);
//    glRotatef(rotation, 0.0, 1.0, 0.0);
//    glCallList(animatedDisplayListId);

//    Q_CHECK(animatedFBO->release());
//    Q_CHECK_GLERROR;
//}

//void Viewport3DPrivate::resize(int w, int h)
//{
//    initFBOs(w, h);
//    dirtyStaticFBO = true;
//    q->update();
//}

} // namespace Internal
} // namespace Editor3D

GLViewport::GLViewport(GLWidgetSplit *split, const QSize &size)
    :   d(new GLViewportPrivate(this, split, size.width(), size.height()))
{
    Q_CHECK_PTR(d);
}

GLViewport::GLViewport(GLWidgetSplit *split, int w, int h)
    :   d(new GLViewportPrivate(this, split, w, h))
{
    Q_CHECK_PTR(d);
}

GLViewport::~GLViewport()
{
    delete d;  d = 0;
}

void GLViewport::setBackgroundColor(const QColor &color)
{
    d->backgroundColor = color;
}

QPoint GLViewport::pos() const
{
    return d->split->pos();
}

QRect GLViewport::rect() const
{
    return d->split->rect();
}

QSize GLViewport::size() const
{
    return d->split->size();
}

void GLViewport::resize(int w, int h)
{
    d->resize(w, h);
}

const QList<GLuint> &GLViewport::textureIds() const
{
    return d->textureIds;
}

void GLViewport::update()
{
}

void GLViewport::draw()
{
    d->widget->drawViewport(this);
}
