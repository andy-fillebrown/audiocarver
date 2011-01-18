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

#include <QtGui/QResizeEvent>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThread>

using namespace Editor3D;

namespace Editor3D {
namespace Internal {

class SwapBuffersThread : public QThread
{
public:
    CentralWidget3D *centralWidget;
    QMutex mutex;
    bool running;

    SwapBuffersThread(CentralWidget3D *centralWidget)
        :   QThread(centralWidget)
        ,   centralWidget(centralWidget)
        ,   running(false)
    {
    }

    virtual ~SwapBuffersThread()
    {
        stop();

        running = false;
        centralWidget = 0;
    }

    virtual void run()
    {
        running = true;
        while (running) {
            QMutexLocker locker(&mutex);
            centralWidget->makeCurrent();
            Q_ASSERT(centralWidget->isValid());
            centralWidget->draw();
            centralWidget->swapBuffers();
            centralWidget->doneCurrent();
        }
    }

    void stop()
    {
        running = false;
        wait();
    }
};

class CentralWidget3DPrivate
{
public:
    CentralWidget3D *q;
    Viewport3D *viewportLeft;
    Viewport3D *viewportRight;
    GLuint displayListId;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;
    int screenOriginId;
    int screenSizeId;
    SwapBuffersThread *swapBuffersThread;

    CentralWidget3DPrivate(CentralWidget3D *q)
        :   q(q)
        ,   viewportLeft(0)
        ,   viewportRight(0)
        ,   displayListId(0)
        ,   vertexShader(0)
        ,   fragmentShader(0)
        ,   shaderProgram(0)
        ,   screenOriginId(-1)
        ,   screenSizeId(-1)
        ,   swapBuffersThread(0)
    {
        q->makeCurrent();
        Q_ASSERT(q->isValid());

        initViewports();
        initShaders();
        initDisplayLists();
        initSwapBuffersThread();
        draw();
    }

    ~CentralWidget3DPrivate()
    {
        swapBuffersThread->stop();
        swapBuffersThread = 0;
        q->makeCurrent();
        Q_ASSERT(q->isValid());

        screenSizeId = -1;
        screenOriginId = -1;
        shaderProgram = 0;
        fragmentShader = 0;
        vertexShader = 0;
        glDeleteLists(displayListId, 1);  displayListId = 0;
        delete viewportRight;  viewportRight = 0;
        delete viewportLeft;  viewportLeft = 0;
        q = 0;
    }

    void initViewports()
    {
        const int w = q->width() / 2;
        const int h = q->height();

        viewportLeft = new Viewport3D(q, w, h);
        viewportLeft->setBackgroundColor(Qt::white);
        viewportLeft->setRotationPerFrame(2);

        viewportRight = new Viewport3D(q, w, h);
        viewportRight->setBackgroundColor(Qt::white);
        viewportRight->setRotationPerFrame(3);
    }

    void initShaders()
    {
        vertexShader = new QGLShader(QGLShader::Vertex, q);
        Q_CHECK(vertexShader->compileSourceFile(":/editor3d/shaders/centralwidget3d_vertex.glsl"));
        if (!vertexShader->isCompiled())
            qDebug() << vertexShader->log();

        fragmentShader = new QGLShader(QGLShader::Fragment, q);
        Q_CHECK(fragmentShader->compileSourceFile(":/editor3d/shaders/centralwidget3d_fragment.glsl"));
        if (!fragmentShader->isCompiled())
            qDebug() << fragmentShader->log();

        shaderProgram = new QGLShaderProgram(q);
        Q_CHECK(shaderProgram->addShader(vertexShader));
        Q_CHECK(shaderProgram->addShader(fragmentShader));
        Q_CHECK(shaderProgram->link());

        screenOriginId = shaderProgram->uniformLocation("screenOrigin");
        screenSizeId = shaderProgram->uniformLocation("screenSize");
        Q_ASSERT(screenOriginId != -1);
        Q_ASSERT(screenSizeId != -1);
        Q_CHECK_GLERROR;
    }

    void initDisplayLists()
    {
        displayListId = glGenLists(1);
        glNewList(displayListId, GL_COMPILE);
        glBegin(GL_TRIANGLES);
        glVertex2f(-2.0, -1.0);
        glVertex2f(2.0, -1.0);
        glVertex2f(0.0, 4.0);
        glEnd();
        glEndList();
        Q_CHECK_GLERROR;
    }

    void initSwapBuffersThread()
    {
        swapBuffersThread = new SwapBuffersThread(q);
    }

    void draw()
    {
        qglPushState();
        viewportLeft->update();
        viewportRight->update();
        Q_CHECK(shaderProgram->bind());

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        const QSize cw = q->size();
        const int modW = cw.width() % 2;
        const int modH = cw.height() % 2;

        const QSize vpL = viewportLeft->size();
        const int vpL_w = vpL.width() + modW;
        const int vpL_h = vpL.height() + modH;
        glViewport(0, 0, vpL_w, vpL_h);
        shaderProgram->setUniformValue(screenOriginId, 0, 0);
        shaderProgram->setUniformValue(screenSizeId, vpL_w, vpL_h);
        glBindTexture(GL_TEXTURE_2D, viewportLeft->staticTextureId());
        glCallList(displayListId);
        glBindTexture(GL_TEXTURE_2D, viewportLeft->animatedTextureId());
        glCallList(displayListId);

        const QSize vpR = viewportRight->size();
        const int vpR_w = vpR.width() + modW;
        const int vpR_h = vpR.height() + modH;
        glViewport(vpL_w, 0, vpR_w, vpR_h);
        shaderProgram->setUniformValue(screenOriginId, vpL_w, 0);
        shaderProgram->setUniformValue(screenSizeId, vpR_w, vpR_h);
        glBindTexture(GL_TEXTURE_2D, viewportRight->staticTextureId());
        glCallList(displayListId);
        glBindTexture(GL_TEXTURE_2D, viewportRight->animatedTextureId());
        glCallList(displayListId);

        shaderProgram->release();
        qglPopState();
        Q_CHECK_GLERROR;
    }
};

} // namespace Internal
} // namespace Editor3D

CentralWidget3D::CentralWidget3D(const QGLFormat &format, QWidget *parent)
    :   QGLWidget(format, parent)
    ,   d(new Internal::CentralWidget3DPrivate(this))
{
    setAutoBufferSwap(false);
    doneCurrent();
    d->swapBuffersThread->start();
}

CentralWidget3D::~CentralWidget3D()
{
    delete d;  d = 0;
}

void CentralWidget3D::draw()
{
    d->draw();
}

void CentralWidget3D::paintEvent(QPaintEvent *)
{
    // do nothing
}

void CentralWidget3D::resizeEvent(QResizeEvent *event)
{
    const QSize &size = event->size();
    int w = size.width() / 2;
    int h = size.height();

    QMutexLocker locker(&d->swapBuffersThread->mutex);
    makeCurrent();
    Q_ASSERT(isValid());
    d->viewportLeft->resize(w, h);
    d->viewportRight->resize(w, h);
    Q_CHECK_GLERROR;
    doneCurrent();
}
