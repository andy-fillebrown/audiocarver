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

#include "glviewport.h"

#include "glwidget.h"
#include "glwidget_p.h"
#include "glwidgetsplit.h"

#include <glsceneplugin/interfaces/iglscene.h>
#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>

#include <GL/glu.h>

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
    GLWidgetSplit *parentSplit;
    GLWidget *widget;
    QGLFramebufferObject *backgroundFBO;
    QGLFramebufferObject *staticFBO;
    QGLFramebufferObject *modelFBO;
    QGLFramebufferObject *editingFBO;
    QGLFramebufferObject *animationFBO;
    QGLFramebufferObject *overlayFBO;

    QColor backgroundColor;
    QList<GLuint> textureIds;

    QVector3D cameraTarget;
    QVector3D cameraPosition;
    QVector3D cameraUpVector;
    qreal dcsWidth;
    qreal dcsHeight;
    bool perspective;

    QMatrix4x4 screenTransform;
    QMatrix4x4 projectionTransform;
    QMatrix4x4 viewTransform;
    QMatrix4x4 worldTransform;

    GLViewportPrivate(GLViewport *q, GLWidgetSplit *parentSplit)
        :   q(q)
        ,   parentSplit(parentSplit)
        ,   widget(parentSplit->widget())
        ,   backgroundFBO(0)
        ,   staticFBO(0)
        ,   modelFBO(0)
        ,   editingFBO(0)
        ,   animationFBO(0)
        ,   overlayFBO(0)
        ,   backgroundColor(QColor(251, 251, 251))
        ,   cameraTarget(0.0, 0.0, 0.0)
        ,   cameraPosition(0.0, 0.0, -100.0)
        ,   cameraUpVector(0.0, 1.0, 0.0)
        ,   dcsWidth(2.0)
        ,   dcsHeight(2.0)
        ,   perspective(true)
    {
        Q_ASSERT(widget);

        initializeGLFunctions(widget->context());
        initializeFBOs(parentSplit->width(), parentSplit->height());
    }

    ~GLViewportPrivate()
    {
        textureIds.clear();

        delete overlayFBO;  overlayFBO = 0;
        delete animationFBO;  animationFBO = 0;
        delete editingFBO;  editingFBO = 0;
        delete modelFBO;  modelFBO = 0;
        delete staticFBO;  staticFBO = 0;
        delete backgroundFBO;  backgroundFBO = 0;
        widget = 0;
        parentSplit = 0;
        q = 0;
    }

    void initializeFBOs(int w, int h)
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
            Q_ASSERT(false && "Invalid fbo type.");
            return 0;
        }
        Q_ASSERT(false && "Invalid fbo type.");
        return 0;
    }

    void updateFBO(int fboId)
    {
        GLScene::IGLScene *scene = widget->currentScene();
        Q_ASSERT(scene && "No scene.");

        QGLFramebufferObject *fbo = this->fbo(fboId);
        Q_ASSERT(fbo && fbo->isValid());

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
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 1000.0);
//        glLoadMatrixd(projectionTransform.data());

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(cameraPosition.x(), cameraPosition.y(), cameraPosition.z(),
                  cameraTarget.x(), cameraTarget.y(), cameraTarget.z(),
                  0, 1, 0);
//        glLoadMatrixd(viewTransform.data());

        bool drewToFBO = false;

        switch (fboId) {
        case BackgroundFBO:
            widget->qglClearColor(backgroundColor);
            glClear(GL_COLOR_BUFFER_BIT);
            scene->drawBackgroundGL();
            drewToFBO = true;
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
            if (widget->isAnimating())
                drewToFBO = scene->drawAnimationGL(widget->animationTime());
            break;
        case OverlayFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawOverlayGL();
            break;
        default:
            Q_ASSERT(false && "Invalid fbo type.");
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
        initializeFBOs(w, h);
        updateAllFBOs();
    }

    void updateTransforms()
    {
        QMatrix4x4 xform;

        // Screen transform.
        xform(0,0) = xform(0,3) = qreal(q->width()) / 2.0;
        xform(1,1) = xform(1,3) = qreal(q->height()) / 2.0;
        if (perspective) {
            xform(2,2) = 3276.75;
            xform(2,3) = 62258.75;
        } else
            xform(2,2) = xform(2,3) = 32767.5;
        screenTransform = xform;

        // Projection transform.
        xform.setToIdentity();
        const qreal targetDistance = (cameraTarget - cameraPosition).length();
        xform(0,0) = 2.0 / dcsWidth;
        xform(1,1) = 2.0 / dcsHeight;
        if (perspective)
            xform(2,2) = xform(3,2) = 1.0 / targetDistance;
        else
            xform(2,2) = 0.1 / targetDistance;
        projectionTransform = xform;

        // View transform.
        xform.setToIdentity();
        QVector3D vz = (cameraTarget - cameraPosition).normalized();
        QVector3D vy = cameraUpVector;
        QVector3D vx = QVector3D::crossProduct(vz, vy);
        xform(0,0) = vx.x();  xform(0,1) = vx.y();  xform(0,2) = vx.z();
        xform(1,0) = vy.x();  xform(1,1) = vy.y();  xform(1,2) = vy.z();
        xform(2,0) = vz.x();  xform(2,1) = vz.y();  xform(2,2) = vz.z();
        QVector3D target = xform.map(cameraTarget);
        target = -target;
        xform(0,3) = target.x();
        xform(1,3) = target.y();
        xform(2,3) = target.z();
        viewTransform = xform;

        // World Transform.
        xform = screenTransform * projectionTransform * viewTransform;
        const qreal scalar = xform(3,3);
        if (scalar != 1.0 && scalar != 0.0)
            xform *= scalar;
        xform(3,3) = 1.0;
        worldTransform = xform;
    }
};

} // namespace Internal
} // namespace Editor3D

GLViewport::GLViewport(GLWidgetSplit *parentSplit)
    :   d(new GLViewportPrivate(this, parentSplit))
{
    Q_CHECK_PTR(d);

    d->updateAllFBOs();
    d->widget->d->appendViewport(this);
}

GLViewport::~GLViewport()
{
    if (!d->widget->d->isBeingDestroyed)
        d->widget->d->removeViewport(this);

    delete d;  d = 0;
}

GLWidgetSplit *GLViewport::parentSplit() const
{
    return d->parentSplit;
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
    return d->parentSplit->pos();
}

QRect GLViewport::rect() const
{
    return d->parentSplit->rect();
}

QSize GLViewport::size() const
{
    return d->parentSplit->size();
}

int GLViewport::width() const
{
    return d->parentSplit->width();
}

int GLViewport::height() const
{
    return d->parentSplit->height();
}

void GLViewport::resize(int width, int height)
{
    d->resizeFBOs(width, height);
}

void GLViewport::updateAnimation()
{
    d->updateFBO(AnimationFBO);
}

void GLViewport::setCameraVectors(const QVector3D &position, const QVector3D &target, const QVector3D &upVector)
{
    d->cameraPosition = position;
    d->cameraTarget = target;
    d->cameraUpVector = upVector;
    d->updateTransforms();
    d->updateAllFBOs();
}

const QVector3D &GLViewport::cameraTarget() const
{
    return d->cameraTarget;
}

void GLViewport::setCameraTarget(const QVector3D &target)
{
    d->cameraTarget = target;
    d->updateTransforms();
    d->updateAllFBOs();
}

const QVector3D &GLViewport::cameraPosition() const
{
    return d->cameraPosition;
}

void GLViewport::setCameraPosition(const QVector3D &position)
{
    d->cameraPosition = position;
    d->updateTransforms();
    d->updateAllFBOs();
}

const QVector3D &GLViewport::cameraUpVector() const
{
    return d->cameraUpVector;
}

void GLViewport::setCameraUpVector(const QVector3D &upVector)
{
    d->cameraUpVector = upVector;
    d->updateTransforms();
    d->updateAllFBOs();
}

bool GLViewport::isPerspective() const
{
    return d->perspective;
}

void GLViewport::setPerspective(bool perspective)
{
    d->perspective = perspective;
    d->updateTransforms();
    d->updateAllFBOs();
}

const QMatrix4x4 &GLViewport::screenTransform() const
{
    return d->screenTransform;
}

const QMatrix4x4 &GLViewport::projectionTransform() const
{
    return d->projectionTransform;
}

const QMatrix4x4 &GLViewport::viewTransform() const
{
    return d->viewTransform;
}

const QMatrix4x4 &GLViewport::worldTransform() const
{
    return d->worldTransform;
}

void GLViewport::paintGL()
{
    const GLWidget *widget = d->widget;
    const QRect rect = this->rect();

    const GLfloat left = rect.left();
    const GLfloat bottom = widget->height() - rect.bottom() - 1;
    const GLfloat width = rect.width();
    const GLfloat height = rect.height();
    Q_ASSERT(0 < width);
    Q_ASSERT(0 < height);

    glViewport(left, bottom, width, height);

    const GLWidgetPrivate *widget_d = widget->d;
    widget_d->shaderProgram->setUniformValue(widget_d->screenOriginId, left, bottom);
    widget_d->shaderProgram->setUniformValue(widget_d->screenSizeId, width, height);

    foreach (const GLuint &id, d->textureIds) {
        if (id == 0)
            continue;
        glBindTexture(GL_TEXTURE_2D, id);
        glCallList(widget_d->displayListId);
    }
}
