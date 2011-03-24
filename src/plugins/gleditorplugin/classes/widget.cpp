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

#include "widget.h"

#include "widget_p.h"
#include "widgetsplit.h"
#include "viewport.h"

#include <glsceneplugin/interfaces/iscene.h>
#include <gleditorplugin/dialogs/behaviorsettingspage.h>
#include <gleditorplugin/dialogs/displaysettingspage.h>

#include <extensionsystem/pluginmanager.h>
#include <gmtl/VecOps.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>
#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

using namespace GL;
using namespace GL::Internal;

Widget::Widget(QWidget *parent)
    :   QGLWidget(parent)
    ,   d(new WidgetPrivate(this))
{
    Q_CHECK_PTR(d);
    d->init();

    d->behaviorSettings = BehaviorSettingsPage::instance()->d->settings;
    connect(BehaviorSettingsPage::instance(),
            SIGNAL(settingsChanged(BehaviorSettings)),
            SLOT(updateBehaviorSettings(BehaviorSettings)));

    d->displaySettings = DisplaySettingsPage::instance()->d->settings;
    connect(DisplaySettingsPage::instance(),
            SIGNAL(settingsChanged(DisplaySettings)),
            SLOT(updateDisplaySettings(DisplaySettings)));

    setMouseTracking(true);
    setCursor(QCursor(Qt::CrossCursor));

    setAnimating(true);
}

Widget::~Widget()
{
    delete d;  d = 0;
}

IScene *Widget::currentScene() const
{
    return d->scene;
}

void Widget::setCurrentScene(IScene *scene)
{
    Q_UNUSED(scene);
    Q_ASSERT(false && "Not implemented yet.");
}

WidgetSplit *Widget::currentSplit() const
{
    return d->currentSplit;
}

void Widget::setCurrentSplit(WidgetSplit *split)
{
    if (d->currentSplit == split)
        return;

    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    // Set old viewport background color to inactive color (light grey).
    Viewport *vp = d->currentSplit ? d->currentSplit->viewport() : 0;
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

Viewport *Widget::currentViewport() const
{
    return currentSplit()->viewport();
}

void Widget::setCurrentViewport(Viewport *viewport)
{
    setCurrentSplit(viewport->parentSplit());
}

void Widget::setAnimating(bool animating)
{
    d->animating = animating;
    if (animating) {
        d->elapsedTime.start();
        QTimer::singleShot(0, this, SLOT(animateGL()));
    }
}

bool Widget::isAnimating() const
{
    return d->animating;
}

qreal Widget::animationTime() const
{
    if (d->elapsedTime.isValid())
        return qreal(d->elapsedTime.elapsed()) / qreal(1000.0);
    return qreal(0.0);
}

void Widget::splitHorizontal()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    WidgetSplit *split = currentSplit();
    split->splitHorizontal();
    setCurrentSplit(split->splitOne());
}

void Widget::splitVertical()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    WidgetSplit *split = currentSplit();
    split->splitVertical();
    setCurrentSplit(split->splitOne());
}

void Widget::removeCurrentSplit()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    WidgetSplit *split = currentSplit()->parentSplit();
    if (!split)
        return;
    split->removeSplit();
    d->currentSplit = 0;
    setCurrentSplit(split);
}

void Widget::removeAllSplits()
{
    Q_ASSERT(isValid());
    Q_ASSERT(context() == QGLContext::currentContext());

    d->mainSplit->removeSplit();
    d->currentSplit = 0;
    setCurrentSplit(d->mainSplit);
}

void Widget::updateBehaviorSettings(const BehaviorSettings &previousSettings)
{
    Q_UNUSED(previousSettings);
}

void Widget::updateDisplaySettings(const DisplaySettings &previousSettings)
{
    Q_UNUSED(previousSettings);
}

void Widget::animateGL()
{
    QCoreApplication::processEvents();

    foreach (Viewport *vp, d->viewports)
        vp->updateAnimation();

    updateGL();

    if (!isAnimating())
        return;

    // Hackish attempt at maintaining 60+ fps.
    // 'd->prevFrameTime' is set in paintGL().
    const qint64 elapsed = d->elapsedTime.elapsed() - d->prevFrameTime;
    const qint64 nextFrameTime = 14 <= elapsed ? 0 : 14 - elapsed;
    QTimer::singleShot(nextFrameTime, this, SLOT(animateGL()));
}

void Widget::paintGL()
{
    if (!d->shaderProgram)
        return;

    GL::pushState();
    Q_CHECK(d->shaderProgram->bind());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    foreach (Viewport *vp, d->viewports)
        vp->paintGL();

    d->shaderProgram->release();
    Q_CHECK_GLERROR;
    GL::popState();

    d->prevFrameTime = d->elapsedTime.elapsed();
}

void Widget::resizeGL(int width, int height)
{
    d->mainSplit->resize(width, height);
    updateGL();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    // If left mouse button is pressed on a viewport, make it current.
    // If left mouse button is pressed on a viewport border, start dragging it.
    if (event->button() == Qt::LeftButton) {
        WidgetSplit *split = d->mainSplit;
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
        // 'split' is only valid if mouse is not on border.
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
            d->draggingViewport = d->viewportAt(pos);

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

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    if (d->draggingSplit) {
        WidgetSplit *split = d->draggingSplit;

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

        WidgetSplit *split = d->mainSplit;
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
        if (cursor().shape() != cursorShape)
            setCursor(QCursor(cursorShape));

        // Don't fall through to pan/rotate if cursor is on border.
        if (isOnBorder)
            return;
    }

    if (d->isPanning) {
        // Calculate drag vector from previous mouse position.
        Viewport *vp = d->draggingViewport;
        const Point startPt = vp->findPointOnCurrentUcs(d->prevDragPos - vp->pos());
        const Point endPt = vp->findPointOnCurrentUcs(pos - vp->pos());
        Vector dragVec = endPt - startPt;
        dragVec[0] = -dragVec[0];

        // Apply translation to viewport's model matrix.
        vp->setModelTranslation(vp->modelTranslation() + dragVec);

        // Update previous mouse position and redraw.
        d->prevDragPos = pos;
        updateGL();

        return;
    }

    if (d->isRotating) {
        Viewport *vp = d->draggingViewport;
        const QSize size = vp->size();
        const QPoint deltaPos = pos - d->prevDragPos;

        // Pause automatic view updating, since two calls to
        // GLViewport::setCameraMatrix might be made.
        vp->pauseAutomaticViewUpdate();

        // Rotate the camera around the target using the y axis as the axis of
        // rotation.
        const real dragX = real(deltaPos.x()) / real(size.width());
        if (dragX != 0.0f) {
            // Calculate rotation matrix using previous mouse position.
            AxisAngle axisAngle(-2.0f * M_PI * dragX, Constants::axisY);
            Matrix m;
            gmtl::setRot(m, axisAngle);

            // Rotate camera's position.
            Point normCamEye = vp->cameraEye() - vp->cameraTarget();
            gmtl::xform(normCamEye, m, normCamEye);
            Point newCamEye = vp->cameraTarget() + normCamEye;

            // Rotate camera's up vector.
            Vector newCamUpVec;
            gmtl::xform(newCamUpVec, m, vp->cameraUpVector());

            // Apply new position and up vector.
            vp->setCameraTransform(newCamEye, newCamUpVec);
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
            Point normCamEye = vp->cameraEye() - vp->cameraTarget();
            gmtl::xform(normCamEye, m, normCamEye);
            Point newCamEye = vp->cameraTarget() + normCamEye;

            // Rotate camera's up vector.
            Vector newCamUpVec;
            gmtl::xform(newCamUpVec, m, vp->cameraUpVector());

            // Apply new position and up vector.
            vp->setCameraTransform(newCamEye, newCamUpVec);
        }

        // Restart automatic view updating.
        vp->resumeAutomaticViewUpdate();

        // Update previous mouse position and redraw.
        d->prevDragPos = pos;
        updateGL();

        return;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        d->draggingSplit = 0;
    else if (event->button() == Qt::RightButton) {
        d->draggingViewport = 0;
        d->isPanning = false;
        d->isRotating = false;
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    // Do nothing if mouse pointer is not over viewport.
    Viewport *vp = d->viewportAt(event->pos());
    if (!vp) {
        event->ignore();
        return;
    }

    // Scale viewport's camera height by plus or minus 1.25 depending on which
    // way mouse wheel rolled.
    real h = vp->cameraHeight();
    const int delta = event->delta();
    if (0 < delta)
        h /= 1.1f * d->behaviorSettings->d.zoomSpeed;
    else
        h *= 1.1f * d->behaviorSettings->d.zoomSpeed;
    vp->setCameraHeight(h);

    updateGL();
}
