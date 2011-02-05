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

#include "glwidget.h"
#include "glwidgetsplit.h"
#include "glviewport.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

#include <QtGui/QMouseEvent>

#include <QtCore/QElapsedTimer>
#include <QtCore/QMutex>
#include <QtCore/QThread>

using namespace GLEditor;

namespace GLEditor {
namespace Internal {

class GLWidgetDrawThread : public QThread
{
public:
    GLWidget *widget;
    QMutex *mutex;
    bool running;
    bool swap;
    bool animating;

    GLWidgetDrawThread(GLWidget *widget)
        :   widget(widget)
        ,   mutex(widget->glDrawMutex())
        ,   running(false)
        ,   swap(false)
        ,   animating(false)
    {
    }

    ~GLWidgetDrawThread()
    {
        stop();

        animating = false;
        swap = false;
        mutex = 0;
        widget = 0;
    }

    virtual void run()
    {
        QElapsedTimer timer;
        running = true;
        while(running) {
            if (!swap) {
                msleep(1);
                continue;
            }
            timer.start();
            mutex->lock();
            widget->makeCurrent();
            Q_ASSERT(widget->isValid());
            Q_ASSERT(widget->context() == QGLContext::currentContext());
            Q_CHECK_GLERROR;

            if (animating)
                widget->paintGL();

            widget->swapBuffers();

            if (!animating)
                swap = false;

            widget->doneCurrent();
            mutex->unlock();

            while (timer.elapsed() < 5)
                msleep(1);
        }
    }

    void stop()
    {
        running = false;
        wait();
    }

    void swapBuffers()
    {
        swap = true;
    }

    void setAnimating(bool animating = true)
    {
        this->animating = animating;
    }
};

class GLWidgetPrivate
{
public:
    GLWidget *q;
    QMutex *drawMutex;
    GLWidgetSplit *mainSplit;
    GLWidgetSplit *currentSplit;
    GLuint displayListId;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;
    int screenOriginId;
    int screenSizeId;
    GLWidgetSplit *draggingSplit;
    GLWidgetDrawThread *drawThread;

    GLWidgetPrivate(GLWidget *q)
        :   q(q)
        ,   drawMutex(new QMutex(QMutex::Recursive))
        ,   mainSplit(0)
        ,   currentSplit(0)
        ,   displayListId(0)
        ,   vertexShader(0)
        ,   fragmentShader(0)
        ,   shaderProgram(0)
        ,   screenOriginId(-1)
        ,   screenSizeId(-1)
        ,   draggingSplit(0)
        ,   drawThread(0)
    {
        Q_CHECK_PTR(drawMutex);
    }

    ~GLWidgetPrivate()
    {
        delete drawThread;  drawThread = 0;

        q->makeCurrent();
        Q_ASSERT(q->isValid());
        Q_ASSERT(q->context() == QGLContext::currentContext());

        draggingSplit = 0;
        screenSizeId = -1;
        screenOriginId = -1;
        shaderProgram = 0;
        fragmentShader = 0;
        vertexShader = 0;
        glDeleteLists(displayListId, 1);  displayListId = 0;
        currentSplit = 0;
        delete mainSplit;  mainSplit = 0;
        delete drawMutex;  drawMutex = 0;
        q = 0;
    }

    void init()
    {
        initSplits();
        initShaders();
        initDisplayLists();
        initDrawThread();
    }

    void initSplits()
    {
        q->makeCurrent();
        Q_ASSERT(q->isValid());
        Q_ASSERT(q->context() == QGLContext::currentContext());

        mainSplit = new GLWidgetSplit(q);
        Q_CHECK_PTR(mainSplit);

        q->setCurrentSplit(mainSplit);
    }

    void initShaders()
    {
        q->makeCurrent();
        Q_ASSERT(q->isValid());
        Q_ASSERT(q->context() == QGLContext::currentContext());

        vertexShader = new QGLShader(QGLShader::Vertex, q);
        Q_CHECK_PTR(vertexShader);
        Q_CHECK(vertexShader->compileSourceFile(":/gleditor/shaders/glwidget_vertex.glsl"));
        if (!vertexShader->isCompiled())
            qDebug() << vertexShader->log();

        fragmentShader = new QGLShader(QGLShader::Fragment, q);
        Q_CHECK_PTR(fragmentShader);
        Q_CHECK(fragmentShader->compileSourceFile(":/gleditor/shaders/glwidget_fragment.glsl"));
        if (!fragmentShader->isCompiled())
            qDebug() << fragmentShader->log();

        shaderProgram = new QGLShaderProgram(q);
        Q_CHECK_PTR(shaderProgram);
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
        q->makeCurrent();
        Q_ASSERT(q->isValid());
        Q_ASSERT(q->context() == QGLContext::currentContext());

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

    void initDrawThread()
    {
        drawThread = new GLWidgetDrawThread(q);
        Q_CHECK_PTR(drawThread);
    }
};

} // namespace Internal
} // namespace Editor3D

GLWidget::GLWidget(QWidget *parent)
    :   QGLWidget(parent)
    ,   d(new Internal::GLWidgetPrivate(this))
{
    Q_CHECK_PTR(d);
    d->init();

    setAutoBufferSwap(false);

    setMouseTracking(true);
    setCursor(QCursor(Qt::CrossCursor));

    doneCurrent();
    d->drawThread->start(QThread::TimeCriticalPriority);

    d->drawThread->setAnimating(true);
}

GLWidget::~GLWidget()
{
    delete d;  d = 0;
}

GLWidgetSplit *GLWidget::currentSplit() const
{
    return d->currentSplit;
}

void GLWidget::setCurrentSplit(GLWidgetSplit *split)
{
    if (d->currentSplit == split)
        return;

    d->drawMutex->lock();
    makeCurrent();
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLViewport *vp = d->currentSplit ? d->currentSplit->viewport() : 0;
    if (vp)
        vp->setBackgroundColor(QColor(251, 251, 251));

    vp = split->viewport();
    if (vp)
        vp->setBackgroundColor(Qt::white);

    paintGL();
    swapBuffers();

    doneCurrent();
    d->drawMutex->unlock();

    d->currentSplit = split;
}

bool GLWidget::isAnimating() const
{
    if (!d->drawThread)
        return false;
    return d->drawThread->animating;
}

void GLWidget::splitHorizontal()
{
    d->drawMutex->lock();
    makeCurrent();
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLWidgetSplit *split = currentSplit();
    split->splitHorizontal();
    setCurrentSplit(split->splitOne());

    doneCurrent();
    d->drawMutex->unlock();
}

void GLWidget::splitVertical()
{
    d->drawMutex->lock();
    makeCurrent();
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLWidgetSplit *split = currentSplit();
    split->splitVertical();
    setCurrentSplit(split->splitOne());

    doneCurrent();
    d->drawMutex->unlock();
}

void GLWidget::removeCurrentSplit()
{
    d->drawMutex->lock();
    makeCurrent();
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLWidgetSplit *split = currentSplit()->parentSplit();
    if (!split)
        return;
    split->removeSplit();
    d->currentSplit = 0;
    setCurrentSplit(split);

    doneCurrent();
    d->drawMutex->unlock();
}

void GLWidget::removeAllSplits()
{
    d->drawMutex->lock();
    makeCurrent();
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    d->mainSplit->removeSplit();
    d->currentSplit = 0;
    setCurrentSplit(d->mainSplit);

    doneCurrent();
    d->drawMutex->unlock();
}

QMutex *GLWidget::glDrawMutex() const
{
    return d->drawMutex;
}

void GLWidget::drawViewport(GLViewport *viewport)
{
    QRect vp = viewport->rect();
    const GLfloat left = vp.left();
    const GLfloat bottom = height() - vp.bottom();
    const GLfloat width = vp.width();
    const GLfloat height = vp.height();
    Q_ASSERT(0 < width);
    Q_ASSERT(0 < height);

    glViewport(left, bottom, width, height);
    d->shaderProgram->setUniformValue(d->screenOriginId, left, bottom);
    d->shaderProgram->setUniformValue(d->screenSizeId, width, height);

    const QList<GLuint> &textureIds = viewport->textureIds();
    foreach (const GLuint &id, textureIds) {
        glBindTexture(GL_TEXTURE_2D, id);
        glCallList(d->displayListId);
    }
}

void GLWidget::paintGL()
{
    if (!d->drawThread)
        return;

    if (d->drawThread->animating)
        d->mainSplit->updateAnimation();

    qglPushState();
    Q_CHECK(d->shaderProgram->bind());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

    d->mainSplit->draw();

    d->shaderProgram->release();
    Q_CHECK_GLERROR;
    qglPopState();

    d->drawThread->swapBuffers();
}

void GLWidget::resizeGL(int width, int height)
{
    d->mainSplit->resize(width, height);
    paintGL();
    swapBuffers();
}

void GLWidget::paintEvent(QPaintEvent *)
{
    // do nothing
}

void GLWidget::resizeEvent(QResizeEvent *event)
{
    const QSize &size = event->size();

    d->drawMutex->lock();
    makeCurrent();
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    resizeGL(size.width(), size.height());

    Q_CHECK_GLERROR;
    doneCurrent();
    d->drawMutex->unlock();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    if (!d->draggingSplit) {
        setCursor(QCursor(Qt::CrossCursor));

        // Change cursor to sizing arrows when over split border.
        GLWidgetSplit *split = d->mainSplit;
        while (split->isSplit()) {
            if (split->splitOne()->rect().contains(pos)) {
                split = split->splitOne();
            } else if (split->splitTwo()->rect().contains(pos)) {
                split = split->splitTwo();
            } else {
                setCursor(QCursor(split->isSplitHorizontal() ? Qt::SizeVerCursor : Qt::SizeHorCursor));
                break;
            }
        }
    } else {
        // Convert mouse position from widget coords to split coords.
        QPoint splitPos = pos;
        splitPos.rx() -= d->draggingSplit->pos().x();
        splitPos.ry() -= d->draggingSplit->pos().y();

        if (d->draggingSplit->isSplitHorizontal())
            d->draggingSplit->setSplitLocation(qreal(splitPos.y()) / qreal(d->draggingSplit->height()));
        else
            d->draggingSplit->setSplitLocation(qreal(splitPos.x()) / qreal(d->draggingSplit->width()));

        d->drawMutex->lock();
        makeCurrent();
        Q_ASSERT(isValid());
        Q_ASSERT(context() == QGLContext::currentContext());

        d->draggingSplit->resize(d->draggingSplit->width(), d->draggingSplit->height());
        paintGL();
        swapBuffers();

        Q_CHECK_GLERROR;
        doneCurrent();
        d->drawMutex->unlock();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    GLWidgetSplit *split = d->mainSplit;
    while (split->isSplit()) {
        if (split->splitOne()->rect().contains(pos)) {
            split = split->splitOne();
        } else if (split->splitTwo()->rect().contains(pos)) {
            split = split->splitTwo();
        } else {
            d->draggingSplit = split;
            split = 0;
            break;
        }
    }
    if (split)
        setCurrentSplit(split);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    d->draggingSplit = 0;
}
