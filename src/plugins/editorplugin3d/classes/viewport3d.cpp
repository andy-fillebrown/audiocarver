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
    Viewport3DPrivate(Viewport3D *q, CentralWidget3D *centralWidget, const QSize &size);
    ~Viewport3DPrivate();

    Viewport3D *q;
    CentralWidget3D *centralWidget;
    QGLFramebufferObject *fbo;
    GLuint displayListId;
    int timerId;
    float rotation;

    void initFBO(int w, int h);
    void initDisplayList();
    void draw();
    void resize(int w, int h);

protected:
    virtual void timerEvent(QTimerEvent *event);
};

Viewport3DPrivate::Viewport3DPrivate(Viewport3D *q, CentralWidget3D *centralWidget, const QSize &size)
    :   q(q)
    ,   centralWidget(centralWidget)
    ,   fbo(0)
    ,   displayListId(0)
    ,   timerId(0)
{
    initFBO(size.width(), size.height());
    initDisplayList();
    draw();
    timerId = startTimer(30);
}

Viewport3DPrivate::~Viewport3DPrivate()
{
    centralWidget->makeCurrent();

    glDeleteLists(displayListId, 1);  displayListId = 0;
    delete fbo;  fbo = 0;
    centralWidget = 0;
    q = 0;
}

void Viewport3DPrivate::initFBO(int w, int h)
{
    centralWidget->makeCurrent();
    delete fbo;
    fbo = new QGLFramebufferObject(w, h);

    Q_ASSERT(fbo->isValid());
}

void Viewport3DPrivate::initDisplayList()
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

    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 4; ++i) {
        centralWidget->qglColor(faceColors[i]);
        for (int j = 0; j < 3; ++j)
            glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
    }
    glEnd();
    glEndList();

    Q_CHECK_GLERROR;
}

// TODO: Fix frustum so view scales correctly when tall and narrow.
void Viewport3DPrivate::draw()
{
    const QSize size = fbo->size();
    const int w = size.width();
    const int h = size.height();
    const GLfloat aspect = w / GLfloat(h ? h : 1);

    centralWidget->makeCurrent();
    Q_CHECK(fbo->bind());

    qglPushState();
    centralWidget->qglClearColor(Qt::white);
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
    glCallList(displayListId);
    qglPopState();

    Q_CHECK(fbo->release());

    Q_CHECK_GLERROR;
}

void Viewport3DPrivate::resize(int w, int h)
{
    initFBO(w, h);
    draw();
}

void Viewport3DPrivate::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != timerId)
        return;
    rotation += 1;
    draw();
    centralWidget->updateGL();
}

} // namespace Internal
} // namespace Editor3D

Viewport3D::Viewport3D(CentralWidget3D *centralWidget, const QSize &size)
    :   d(new Viewport3DPrivate(this, centralWidget, size))
{
}

Viewport3D::~Viewport3D()
{
    delete d;
    d = 0;
}

CentralWidget3D *Viewport3D::centralWidget() const
{
    return d->centralWidget;
}

QSize Viewport3D::size() const
{
    return d->fbo->size();
}

GLuint Viewport3D::textureId() const
{
    return d->fbo->texture();
}

void Viewport3D::update()
{
    d->draw();
}

void Viewport3D::startCameraDrag(const QPoint &startPoint)
{
    Q_UNUSED(startPoint);
}

void Viewport3D::resize(int w, int h)
{
    d->resize(w, h);
}
