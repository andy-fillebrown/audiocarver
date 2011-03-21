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

#include <gmtl/Generate.h>
#include <gmtl/Intersection.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/VecOps.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>

#include <GL/glu.h>

using namespace GL;
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

    Point cameraPosition;
    Point cameraTarget;
    Vector cameraUpVector;
    bool perspective;

    Matrix projXform;
    Matrix viewXform;
    Matrix modelXform;
    Matrix inverseXform; // inverted projXform * viewXform, for unprojecting

    Plane ucsPlane;

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
        ,   cameraPosition(0.0, 0.0, -10.0)
        ,   cameraTarget(0.0, 0.0, 0.0)
        ,   cameraUpVector(0.0, 1.0, 0.0)
        ,   perspective(false)
        ,   ucsPlane(Vector(0.0f, 0.0f, -1.0f), 0.0f)
    {
        Q_ASSERT(widget);

        initializeGLFunctions(widget->context());
        initializeFBOs(parentSplit->width(), parentSplit->height());

        updateXforms();
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

        Q_CHECK(fbo->bind());
        qglPushState();

        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_FLAT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

        const QSize size = q->size();
        glViewport(0, 0, size.width(), size.height());
        pushXforms();

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
        updateXforms();
        updateAllFBOs();
    }

    real aspect() const
    {
        const QSize size = parentSplit->size();
        const int h = size.height();
        return real(size.width()) / real(h ? h : 1);
    }

    void updateXforms()
    {
        GL::lookAt(viewXform, cameraPosition, cameraTarget, cameraUpVector);
        GL::perspective(projXform, 45.0f, aspect(), 1.0f, 100.0f);

        inverseXform = projXform * viewXform;
        gmtl::invertFull(inverseXform, inverseXform);
    }

    void pushXforms()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(projXform.mData);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glLoadMatrixf(viewXform.mData);
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

void GLViewport::setCamera(const Point &position, const Point &target, const Vector &upVector)
{
    d->cameraPosition = position;
    d->cameraTarget = target;
    d->cameraUpVector = upVector;
    d->updateXforms();
    d->updateAllFBOs();
}

const Point &GLViewport::cameraPosition() const
{
    return d->cameraPosition;
}

void GLViewport::setCameraPosition(const Point &position)
{
    d->cameraPosition = position;
    d->updateXforms();
    d->updateAllFBOs();
}

const Point &GLViewport::cameraTarget() const
{
    return d->cameraTarget;
}

void GLViewport::setCameraTarget(const Point &target)
{
    d->cameraTarget = target;
    d->updateXforms();
    d->updateAllFBOs();
}

const Vector &GLViewport::cameraUpVector() const
{
    return d->cameraUpVector;
}

void GLViewport::setCameraUpVector(const Vector &upVector)
{
    d->cameraUpVector = upVector;
    d->updateXforms();
    d->updateAllFBOs();
}

bool GLViewport::isPerspective() const
{
    return d->perspective;
}

void GLViewport::setPerspective(bool perspective)
{
    d->perspective = perspective;
    d->updateXforms();
    d->updateAllFBOs();
}

const Matrix &GLViewport::projXform() const
{
    return d->projXform;
}

const Matrix &GLViewport::modelXform() const
{
    return d->modelXform;
}

const Matrix &GLViewport::viewXform() const
{
    return d->viewXform;
}

Point GLViewport::findUcsPoint(const QPoint &screenPos) const
{
    const QSize size = this->size();
    const real w = size.width();
    const real h = size.height();
    const real posX = screenPos.x();
    const real posY = screenPos.y();

    // Transform screenPos to normalized device coordinates.
    const real x = (2.0f * posX / w) - 1.0f;
    const real y = -((2.0f * posY / h) - 1.0f);

    // Cache values common to start and end point transformations.
    const real *m = d->inverseXform.mData;
    const real baseDenom = m[3] * x + m[7] * y + m[15];
    const real baseX = m[0] * x + m[4] * y + m[12];
    const real baseY = m[1] * x + m[5] * y + m[13];
    const real baseZ = m[2] * x + m[6] * y + m[14];

    // Calculate ray's start point.
    const real startDenom = 1.0f / baseDenom;
    if (startDenom == 0.0f) {
        Q_ASSERT(false ** "Can't calculate ray start point.");
        return Point();
    }
    const Point startPt(
        startDenom * baseX,
        startDenom * baseY,
        startDenom * baseZ);

    // Calculate ray's end point.
    const real endDenom = 1.0f / (baseDenom + m[11]);
    if (endDenom == 0.0f) {
        Q_ASSERT(false && "Can't calculate ray end point.");
        return Point();
    }
    const Point endPt(
        endDenom * (baseX + m[8]),
        endDenom * (baseY + m[9]),
        endDenom * (baseZ + m[10]));

    // Find intersection of ray and ucs plane.
    Ray ray(startPt, endPt - startPt);
    real t;
    bool hit = gmtl::intersect(d->ucsPlane, ray, t);
    if (hit && t != 0.0f) {
        Point pt = ray.mOrigin + ray.mDir * t;
        pt[0] = -pt[0]; // ... don't know why x coord needs negation
        return pt;
    }

    return Point();
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
