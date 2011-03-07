/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "glwidget_p.h"
#include "glwidgetsplit.h"
#include "glviewport.h"

#include <glsceneplugin/interfaces/iglscene.h>
#include <extensionsystem/pluginmanager.h>
#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

#include <QtGui/QMouseEvent>

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

using namespace GLEditor;

GLWidget::GLWidget(QWidget *parent)
    :   QGLWidget(parent)
    ,   d(new Internal::GLWidgetPrivate(this))
{
    Q_CHECK_PTR(d);
    d->initialize();

    setMouseTracking(true);
    setCursor(QCursor(Qt::CrossCursor));

    setAnimating(true);
}

GLWidget::~GLWidget()
{
    delete d;  d = 0;
}

GLScene::IGLScene *GLWidget::currentScene() const
{
    return d->scene;
}

void GLWidget::setCurrentScene(GLScene::IGLScene *scene)
{
    Q_UNUSED(scene);
    Q_ASSERT(false && "Not implemented yet");
}

GLWidgetSplit *GLWidget::currentSplit() const
{
    return d->currentSplit;
}

void GLWidget::setCurrentSplit(GLWidgetSplit *split)
{
    if (d->currentSplit == split)
        return;

    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLViewport *vp = d->currentSplit ? d->currentSplit->viewport() : 0;
    if (vp)
        vp->setBackgroundColor(QColor(251, 251, 251));

    vp = split->viewport();
    if (vp)
        vp->setBackgroundColor(Qt::white);

    d->currentSplit = split;

    updateGL();
}

GLViewport *GLWidget::currentViewport() const
{
    return currentSplit()->viewport();
}

void GLWidget::setCurrentViewport(GLViewport *viewport)
{
    setCurrentSplit(viewport->parentSplit());
}

void GLWidget::setAnimating(bool animating)
{
    d->animating = animating;
    if (animating) {
        d->elapsedTime.start();
        QTimer::singleShot(0, this, SLOT(animateGL()));
    }
}

bool GLWidget::isAnimating() const
{
    return d->animating;
}

qreal GLWidget::animationTime() const
{
    if (d->elapsedTime.isValid())
        return qreal(d->elapsedTime.elapsed()) / qreal(1000.0);
    return qreal(0.0);
}

void GLWidget::splitHorizontal()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLWidgetSplit *split = currentSplit();
    split->splitHorizontal();
    setCurrentSplit(split->splitOne());
}

void GLWidget::splitVertical()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLWidgetSplit *split = currentSplit();
    split->splitVertical();
    setCurrentSplit(split->splitOne());
}

void GLWidget::removeCurrentSplit()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    GLWidgetSplit *split = currentSplit()->parentSplit();
    if (!split)
        return;
    split->removeSplit();
    d->currentSplit = 0;
    setCurrentSplit(split);
}

void GLWidget::removeAllSplits()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    d->mainSplit->removeSplit();
    d->currentSplit = 0;
    setCurrentSplit(d->mainSplit);
}

void GLWidget::animateGL()
{
    QCoreApplication::processEvents();

    foreach (GLViewport *viewport, d->viewports)
        viewport->updateAnimation();

    updateGL();

    if (isAnimating())
        QTimer::singleShot(0, this, SLOT(animateGL()));
}

void GLWidget::paintGL()
{
    if (!d->shaderProgram)
        return;

    qglPushState();
    Q_CHECK(d->shaderProgram->bind());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    foreach (GLViewport *viewport, d->viewports)
        viewport->paintGL();

    d->shaderProgram->release();
    Q_CHECK_GLERROR;
    qglPopState();
}

void GLWidget::resizeGL(int width, int height)
{
    d->mainSplit->resize(width, height);
    updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    if (d->draggingSplit) {
       // Convert mouse position from widget coords to split coords.
       QPoint splitPos = pos;
       splitPos.rx() -= d->draggingSplit->pos().x();
       splitPos.ry() -= d->draggingSplit->pos().y();

       if (d->draggingSplit->isSplitHorizontal())
           d->draggingSplit->setSplitLocation(qreal(splitPos.y()) / qreal(d->draggingSplit->height()));
       else
           d->draggingSplit->setSplitLocation(qreal(splitPos.x()) / qreal(d->draggingSplit->width()));

       d->draggingSplit->resize(d->draggingSplit->width(), d->draggingSplit->height());
       updateGL();

       Q_CHECK_GLERROR;
       return;
    }

    if (!d->draggingSplit) {
        // Change cursor to sizing arrows when over split border.
        bool isOnBorder = false;

        GLWidgetSplit *split = d->mainSplit;
        while (split->isSplit()) {
            if (split->splitOne()->rect().contains(pos)) {
                split = split->splitOne();
            } else if (split->splitTwo()->rect().contains(pos)) {
                split = split->splitTwo();
            } else {
                isOnBorder = true;
                break;
            }
        }
        const Qt::CursorShape currentCursorShape = cursor().shape();
        Qt::CursorShape desiredCursorShape = Qt::CrossCursor;
        if (isOnBorder)
            desiredCursorShape = split->isSplitHorizontal() ? Qt::SizeVerCursor
                                                            : Qt::SizeHorCursor;
        if (currentCursorShape != desiredCursorShape)
            setCursor(QCursor(desiredCursorShape));

        return;
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

void GLWidget::mouseReleaseEvent(QMouseEvent *)
{
    d->draggingSplit = 0;
}
