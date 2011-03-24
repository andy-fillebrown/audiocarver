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

#include "widget_p.h"

#include "widget.h"
#include "widgetsplit.h"
#include "viewport.h"

#include <glsceneplugin/interfaces/iscene.h>

#include <extensionsystem/pluginmanager.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

namespace GL {
namespace Internal {

WidgetPrivate::WidgetPrivate(Widget *q)
    :   q(q)
    ,   scene(0)
    ,   mainSplit(0)
    ,   currentSplit(0)
    ,   displayListId(0)
    ,   vertexShader(0)
    ,   fragmentShader(0)
    ,   shaderProgram(0)
    ,   screenOriginId(-1)
    ,   screenSizeId(-1)
    ,   draggingSplit(0)
    ,   draggingViewport(0)
    ,   isPanning(false)
    ,   isRotating(false)
    ,   prevFrameTime(0)
    ,   animating(false)
    ,   isBeingDestroyed(false)
    ,   behaviorSettings(0)
    ,   displaySettings(0)
{
}

WidgetPrivate::~WidgetPrivate()
{
    displaySettings = 0;
    behaviorSettings = 0;

    isBeingDestroyed = true;

    q->makeCurrent();
    Q_ASSERT(q->isValid());
    Q_ASSERT(q->context() == QGLContext::currentContext());

    viewports.clear();

    animating = false;
    draggingSplit = 0;
    screenSizeId = -1;
    screenOriginId = -1;
    shaderProgram = 0;
    fragmentShader = 0;
    vertexShader = 0;
    glDeleteLists(displayListId, 1);  displayListId = 0;
    currentSplit = 0;
    delete mainSplit;  mainSplit = 0;
    scene->destroy();  scene = 0;
    q = 0;
}

void WidgetPrivate::initialize()
{
    initializeScene();
    initializeSplits();
    initializeShaders();
    initializeDisplayLists();
}

void WidgetPrivate::appendViewport(Viewport *viewport)
{
    Q_ASSERT(!viewports.contains(viewport));
    if (viewports.contains(viewport))
        return;
    viewports.append(viewport);
}

void WidgetPrivate::removeViewport(Viewport *viewport)
{
    Q_ASSERT(viewports.contains(viewport));
    viewports.removeOne(viewport);
    Q_ASSERT(!viewports.contains(viewport));
}

Viewport *WidgetPrivate::viewportAtPosition(const QPoint &position) const
{
    foreach (Viewport *viewport, viewports)
        if (viewport->rect().contains(position))
            return viewport;
    return 0;
}

void WidgetPrivate::initializeScene()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    scene = pm->getObject<IScene>();
    Q_ASSERT(scene);

    q->makeCurrent();
    Q_ASSERT(q->isValid());
    Q_ASSERT(q->context() == QGLContext::currentContext());

    scene->initialize();
}

void WidgetPrivate::initializeSplits()
{
    q->makeCurrent();
    Q_ASSERT(q->isValid());
    Q_ASSERT(q->context() == QGLContext::currentContext());

    mainSplit = new WidgetSplit(q);
    Q_CHECK_PTR(mainSplit);

    q->setCurrentSplit(mainSplit);
}

void WidgetPrivate::initializeShaders()
{
    q->makeCurrent();
    Q_ASSERT(q->isValid());
    Q_ASSERT(q->context() == QGLContext::currentContext());

    vertexShader = new QGLShader(QGLShader::Vertex, q);
    Q_CHECK_PTR(vertexShader);
    Q_CHECK(vertexShader->compileSourceFile(":/gleditor/shaders/widget_vertex.glsl"));
    if (!vertexShader->isCompiled())
        qDebug() << vertexShader->log();

    fragmentShader = new QGLShader(QGLShader::Fragment, q);
    Q_CHECK_PTR(fragmentShader);
    Q_CHECK(fragmentShader->compileSourceFile(":/gleditor/shaders/widget_fragment.glsl"));
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

void WidgetPrivate::initializeDisplayLists()
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

} // namespace Internal
} // namespace GL
