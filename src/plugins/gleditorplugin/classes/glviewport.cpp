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

#include <glsceneplugin/interfaces/iglscene.h>

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLFunctions>

using namespace GLEditor;
using namespace GLEditor::Internal;

namespace GLEditor {
namespace Internal {

enum {
    BackgroundFBO = 0,
    StaticFBO,
    ModelFBO,
    EditingFBO,
    AnimationFBO,
    OverlayFBO,
    LastFBO
};

class GLViewportPrivate : protected QGLFunctions
{
public:
    GLViewport *q;
    GLWidget *widget;
    GLWidgetSplit *split;
    QColor backgroundColor;
    QGLFramebufferObject *backgroundFBO;
    QGLFramebufferObject *staticFBO;
    QGLFramebufferObject *modelFBO;
    QGLFramebufferObject *editingFBO;
    QGLFramebufferObject *animationFBO;
    QGLFramebufferObject *overlayFBO;
    QList<GLuint> textureIds;

    GLViewportPrivate(GLViewport *q, GLWidgetSplit *split)
        :   q(q)
        ,   widget(split->widget())
        ,   split(split)
        ,   backgroundColor(QColor(251, 251, 251))
        ,   backgroundFBO(0)
        ,   staticFBO(0)
        ,   modelFBO(0)
        ,   editingFBO(0)
        ,   animationFBO(0)
        ,   overlayFBO(0)
    {
        initializeGLFunctions(widget->context());
        initFBOs(split->width(), split->height());
    }

    ~GLViewportPrivate()
    {
        delete overlayFBO;  overlayFBO = 0;
        delete animationFBO;  animationFBO = 0;
        delete editingFBO;  editingFBO = 0;
        delete modelFBO;  modelFBO = 0;
        delete staticFBO;  staticFBO = 0;
        delete backgroundFBO;  backgroundFBO = 0;
        split = 0;
        widget = 0;
        q = 0;
    }

    void initFBOs(int w, int h)
    {
        if (w < 1)
            w = 1;
        if (h < 1)
            h = 1;

        delete backgroundFBO;
        backgroundFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(backgroundFBO);
        Q_ASSERT(backgroundFBO->isValid());

        delete staticFBO;
        staticFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(staticFBO);
        Q_ASSERT(staticFBO->isValid());

        delete modelFBO;
        modelFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(modelFBO);
        Q_ASSERT(modelFBO->isValid());

        delete editingFBO;
        editingFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(editingFBO);
        Q_ASSERT(editingFBO->isValid());

        delete animationFBO;
        animationFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(animationFBO);
        Q_ASSERT(animationFBO->isValid());

        delete overlayFBO;
        overlayFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(overlayFBO);
        Q_ASSERT(overlayFBO->isValid());

        textureIds.clear();
        textureIds.append(backgroundFBO->texture());
        textureIds.append(staticFBO->texture());
        textureIds.append(modelFBO->texture());
        textureIds.append(editingFBO->texture());
        textureIds.append(animationFBO->texture());
        textureIds.append(overlayFBO->texture());
    }

    QGLFramebufferObject *fbo(int type)
    {
        switch (type) {
        case BackgroundFBO:
            return backgroundFBO;
        case StaticFBO:
            return staticFBO;
        case ModelFBO:
            return modelFBO;
        case EditingFBO:
            return editingFBO;
        case AnimationFBO:
            return animationFBO;
        case OverlayFBO:
            return overlayFBO;
        default:
            Q_ASSERT(false && "Invalid fbo type");
            return 0;
        }
        Q_ASSERT(false && "Invalid fbo type");
        return 0;
    }

    void updateFBO(int fboId)
    {
        GLScene::IGLScene *scene = widget->currentScene();
        Q_ASSERT(scene && "No scene");

        QGLFramebufferObject *fbo = this->fbo(fboId);
        Q_CHECK(fbo);
        Q_ASSERT(fbo->isValid());

        bool drewToFBO = true;

        const QSize size = q->size();
        const int w = size.width();
        const int h = size.height();
        const qreal aspect = size.width() / qreal(size.height() ? size.height() : 1);

        Q_CHECK(fbo->bind());
        qglPushState();

        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_FLAT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0, 0, w, h);
        glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
        glTranslatef(0.0, 0.0, -10.0);

        switch (fboId) {
        case BackgroundFBO:
            widget->qglClearColor(backgroundColor);
            glClear(GL_COLOR_BUFFER_BIT);
            scene->drawBackgroundGL();
            break;
        case StaticFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawStaticGL();
            break;
        case ModelFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawModelGL();
            break;
        case EditingFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawEditingGL();
            break;
        case AnimationFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawAnimationGL(widget->animationTime());
            break;
        case OverlayFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawOverlayGL();
            break;
        default:
            Q_ASSERT(false && "Invalid fbo type");
        }

        qglPopState();
        Q_CHECK(fbo->release());
        Q_CHECK_GLERROR;

        if (drewToFBO)
            textureIds[fboId] = fbo->texture();
        else
            textureIds[fboId] = 0;
    }

    void updateAllFBOs()
    {
        for (int i = 0;  i < LastFBO;  ++i)
            updateFBO(i);
    }

    void resizeFBOs(int w, int h)
    {
        initFBOs(w, h);
        updateAllFBOs();
    }
};

} // namespace Internal
} // namespace Editor3D

GLViewport::GLViewport(GLWidgetSplit *split)
    :   d(new GLViewportPrivate(this, split))
{
    Q_CHECK_PTR(d);
    d->updateAllFBOs();
}

GLViewport::~GLViewport()
{
    delete d;  d = 0;
}

QColor GLViewport::backgroundColor() const
{
    return d->backgroundColor;
}

void GLViewport::setBackgroundColor(const QColor &color)
{
    if (d->backgroundColor == color)
        return;

    d->backgroundColor = color;
    d->backgroundColor.setAlphaF(1.0);

    d->updateFBO(BackgroundFBO);
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
    d->resizeFBOs(w, h);
}

void GLViewport::updateAnimation()
{
    d->updateFBO(AnimationFBO);
}

const QList<GLuint> &GLViewport::textureIds() const
{
    return d->textureIds;
}

void GLViewport::draw()
{
    d->widget->drawViewport(this);
}
