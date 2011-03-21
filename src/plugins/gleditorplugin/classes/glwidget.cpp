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

#include <gmtl/VecOps.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>
#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

using namespace GL;
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
    Q_ASSERT(false && "Not implemented yet.");
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

    // Set old viewport background color to inactive color (light grey).
    GLViewport *vp = d->currentSplit ? d->currentSplit->viewport() : 0;
    if (vp)
        vp->setBackgroundColor(QColor(251, 251, 251));

    // Set current viewport background color to active color (white).
    vp = split->viewport();
    if (vp)
        vp->setBackgroundColor(Qt::white);

    // Update current split and redraw.
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

    if (!isAnimating())
        return;

    // Hackish attempt at maintaining 60 fps.
    // 'd->prevFrameTime' is set in paintGL().
    const qint64 elapsed = d->elapsedTime.elapsed() - d->prevFrameTime;
    const qint64 nextFrameTime = 14 <= elapsed ? 0 : 14 - elapsed;
    QTimer::singleShot(nextFrameTime, this, SLOT(animateGL()));
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

    d->prevFrameTime = d->elapsedTime.elapsed();
}

void GLWidget::resizeGL(int width, int height)
{
    d->mainSplit->resize(width, height);
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    // If left mouse button is pressed on a viewport, make it current.
    // If left mouse button is pressed on a viewport border, start dragging it.
    if (event->button() == Qt::LeftButton) {
        GLWidgetSplit *split = d->mainSplit;
        while (split->isSplit()) {
            if (split->splitOne()->rect().contains(pos))
                split = split->splitOne();
            else if (split->splitTwo()->rect().contains(pos))
                split = split->splitTwo();
            else {
                // On border.
                d->draggingSplit = split;
                split = 0;
                break;
            }
        }
        // 'split' is not zero if not on border.
        if (split)
            setCurrentSplit(split);

        return;
    }

    // Start panning or rotating if mouse is not over a viewport border.
    if (event->button() == Qt::RightButton) {
        d->dragStartScreenPosition = pos;

        if (QApplication::keyboardModifiers() & Qt::ControlModifier)
            d->isRotating = true;
        else
            d->isPanning = true;

        if (d->isPanning || d->isRotating) {
            d->draggingViewport = d->viewportAtPosition(pos);

            // If mouse is over a viewport, d->draggingViewport will be valid,
            // otherwise the mouse is over a viewport border and panning or
            // rotating should not be started.
            if (d->draggingViewport)
                d->prevDragPos = pos;
            else
                d->isPanning = d->isRotating = false;
        }
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    if (d->draggingSplit) {
        GLWidgetSplit *split = d->draggingSplit;

       // Convert mouse position from widget coords to split coords.
       QPoint splitPos = pos;
       splitPos.rx() -= split->pos().x();
       splitPos.ry() -= split->pos().y();

       // Move split location.
       if (split->isSplitHorizontal())
           split->setSplitLocation(qreal(splitPos.y()) / qreal(split->height()));
       else
           split->setSplitLocation(qreal(splitPos.x()) / qreal(split->width()));

       // Update child splits and redraw.
       split->resize(split->width(), split->height());
       updateGL();

       return;
    }

    if (!d->draggingSplit) {
        // Change cursor to sizing arrows when over split border.
        bool isOnBorder = false;

        GLWidgetSplit *split = d->mainSplit;
        while (split->isSplit()) {
            if (split->splitOne()->rect().contains(pos))
                split = split->splitOne();
            else if (split->splitTwo()->rect().contains(pos))
                split = split->splitTwo();
            else {
                isOnBorder = true;
                break;
            }
        }

        // Figure out which cursor shape to use.
        Qt::CursorShape cursorShape = Qt::CrossCursor;
        if (isOnBorder)
            cursorShape = split->isSplitHorizontal() ? Qt::SizeVerCursor : Qt::SizeHorCursor;

        // Change cursor shape, if necessary.
        if (cursor().shape() != desiredCursorShape)
            setCursor(QCursor(desiredCursorShape));

        // Don't fall through to pan/rotate if cursor is on border.
        if (isOnBorder)
            return;
    }

    if (d->isPanning) {
        // Calculate drag vector from previous mouse position.
        GLViewport *vp = d->draggingViewport;
        const Point startPt = vp->findPointOnUcs(d->prevDragPos - vp->pos());
        const Point endPt = vp->findPointOnUcs(pos - vp->pos());
        Point dragVec = endPt - startPt;
        dragVec[1] = -dragVec[1];

        const Point camPos = vp->cameraPosition() + dragVec;
        const Point camTar = vp->cameraTarget() + dragVec;
        vp->setCamera(camPos, camTar, Vector(0.0f, 1.0f, 0.0f));

        // Update previous mouse position and redraw.
        d->prevDragPos = pos;
        updateGL();

        return;
    }

    if (d->isRotating) {
        GLViewport *vp = d->draggingViewport;
        const QSize size = vp->size();
        const QPoint deltaPos = pos - d->prevDragPos;

        // Pause automatic view updating, since we may be making two calls to
        // GLViewport::setCamera.
        vp->pushViewAutomaticUpdate();

        // Rotate the camera around the target using the y axis as the axis of
        // rotation.
        const real dragX = real(deltaPos.x()) / real(size.width());
        if (dragX != 0.0f) {
            // Calculate rotation matrix using previous mouse position.
            AxisAngle axisAngle(-2.0f * M_PI * dragX, GL::yAxis);
            Matrix m;
            gmtl::setRot(m, axisAngle);

            // Rotate camera's position.
            Point normCamPos = vp->cameraPosition() - vp->cameraTarget();
            gmtl::xform(normCamPos, m, normCamPos);
            Point newCamPos = vp->cameraTarget() + normCamPos;

            // Rotate camera's up vector.
            Vector newCamUpVec;
            gmtl::xform(newCamUpVec, m, vp->cameraUpVector());

            // Apply new position and up vector.
            vp->setCamera(newCamPos, vp->cameraTarget(), newCamUpVec);
        }

        // Rotate the camera around the target using the camera's side vector
        // as the axis of rotation.
        const real dragY = real(deltaPos.y()) / real(size.height());
        if (dragY != 0.0f) {
            // Calculate rotation matrix using previous mouse position.
            AxisAngle axisAngle(-2.0f * M_PI * dragY, vp->cameraSideVector());
            Matrix m;
            gmtl::setRot(m, axisAngle);

            // Rotate camera's position.
            Point normCamPos = vp->cameraPosition() - vp->cameraTarget();
            gmtl::xform(normCamPos, m, normCamPos);
            Point newCamPos = vp->cameraTarget() + normCamPos;

            // Rotate camera's up vector.
            Vector newCamUpVec;
            gmtl::xform(newCamUpVec, m, vp->cameraUpVector());

            // Apply new position and up vector.
            vp->setCamera(newCamPos, vp->cameraTarget(), newCamUpVec);
        }

        // Restart automatic view updating.
        vp->popViewAutomaticUpdate();

        // Update previous mouse position and redraw.
        d->prevDragPos = pos;
        updateGL();

        return;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        d->draggingSplit = 0;
    else if (event->button() == Qt::RightButton) {
        d->draggingViewport = 0;
        d->isPanning = false;
        d->isRotating = false;
    }
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    // Do nothing if mouse pointer is not over viewport.
    GLViewport *vp = d->viewportAtPosition(event->pos());
    if (!vp) {
        event->ignore();
        return;
    }

    // Scale viewport's camera height by plus or minus 1.25 depending on which
    // way mouse wheel rolled.
    real h = vp->cameraHeight();
    const int delta = event->delta();
    if (0 < delta)
        h /= 1.25f;
    else
        h *= 1.25f;
    vp->setCameraHeight(h);

    updateGL();
}
