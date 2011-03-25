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

#include "viewport.h"

#include "widget.h"
#include "widget_p.h"
#include "widgetsplit.h"

#include <glsceneplugin/classes/buffer.h>
#include <glsceneplugin/interfaces/iscene.h>

#include <gmtl/Generate.h>
#include <gmtl/Intersection.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/VecOps.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLShaderProgram>

using namespace GL;
using namespace GL::Internal;

namespace GL {
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

class ViewportPrivate
{
public:
    Viewport *q;
    WidgetSplit *parentSplit;
    Widget *widget;
    QGLFramebufferObject *backgroundFBO;
    QGLFramebufferObject *staticFBO;
    QGLFramebufferObject *modelFBO;
    QGLFramebufferObject *editingFBO;
    QGLFramebufferObject *animationFBO;
    QGLFramebufferObject *overlayFBO;

    QColor backgroundColor;
    QList<GLuint> textureIds;

    bool autoViewUpdate;
    bool autoViewUpdatePaused;

    bool perspective;
    Point cameraEye;
    Point cameraTarget;
    Vector cameraUpVector;   // normalized

    real cameraDistanceToTarget;
    real cameraHeight;
    Vector cameraViewVector; // not normalized
    Vector cameraViewDir;    // normalized
    Vector cameraSideVector; // normalized

    Vector modelTranslation; // not normalized
    real modelScaleX;
    real modelScaleY;
    real modelScaleZ;

    Matrix projXform;
    Matrix viewXform;
    Matrix modelXform;

    Matrix projViewXform;      // projXform * viewXform
    Matrix inverseXform;       // inverted projXfrom * viewXform * modelXform
    Matrix inverseCameraXform; // inverted projXform * viewXform

    Plane ucs;

    VertexBuffer *staticVBO;
    VertexArray *staticVA;
    IndexBuffer *staticIBO;
    IndexArray *staticIA;

    ViewportPrivate(Viewport *q, WidgetSplit *parentSplit)
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
        ,   autoViewUpdate(true)
        ,   autoViewUpdatePaused(false)
        ,   perspective(true)
        ,   cameraEye(0.0f, 0.0f, 100.0f)
        ,   cameraTarget(0.0f, 0.0f, 0.0f)
        ,   cameraUpVector(Constants::axisY)
        ,   cameraDistanceToTarget(qAbs(cameraEye[2]))
        ,   cameraHeight(0.1f)
        ,   cameraViewVector(cameraTarget - cameraEye)
        ,   cameraViewDir(0.0f, 0.0f, 1.0f)
        ,   cameraSideVector(Constants::axisY)
        ,   modelTranslation(0.0f, 0.0f, 0.0f)
        ,   modelScaleX(1.0f)
        ,   modelScaleY(1.0f)
        ,   modelScaleZ(1.0f)
        ,   ucs(Constants::planeXY)
        ,   staticVBO(new VertexBuffer(4, q))
        ,   staticVA(new VertexArray(4, staticVBO))
        ,   staticIBO(new IndexBuffer(6, q))
        ,   staticIA(new IndexArray(6, staticIBO))
    {
        Q_ASSERT(widget);

        initFBOs(parentSplit->width(), parentSplit->height());
        initStaticBuffers();

        updateCamera();
        updateModelXform();
    }

    ~ViewportPrivate()
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
            Q_ASSERT(false && "Invalid fbo type.");
            return 0;
        }
        Q_ASSERT(false && "Invalid fbo type.");
        return 0;
    }

    void updateFBO(int fboId)
    {
        IScene *scene = widget->currentScene();
        Q_ASSERT(scene && "No scene.");

        QGLFramebufferObject *fbo = this->fbo(fboId);
        Q_ASSERT(fbo && fbo->isValid());

        Q_CHECK(fbo->bind());
        GL::pushState();

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

        const QSize size = parentSplit->size();
        glViewport(0, 0, size.width(), size.height());
        pushXforms();

        bool drewToFBO = false;

        switch (fboId) {
        case BackgroundFBO:
            widget->qglClearColor(backgroundColor);
            glClear(GL_COLOR_BUFFER_BIT);
            scene->drawBackground();
            drewToFBO = true;
            break;
        case StaticFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drawStatic();
            drewToFBO = scene->drawStatic();
            break;
        case ModelFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawModel();
            break;
        case EditingFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawEdit();
            break;
        case AnimationFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            if (widget->isAnimating())
                drewToFBO = scene->drawAnimation(widget->animationTime());
            break;
        case OverlayFBO:
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            drewToFBO = scene->drawOverlay();
            break;
        default:
            Q_ASSERT(false && "Invalid fbo type.");
        }

        GL::popState();
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
        updateCamera();
    }

    real aspect() const
    {
        const QSize size = parentSplit->size();
        const int h = size.height();
        return real(size.width()) / real(h ? h : 1);
    }

    void updateCamera()
    {
        cameraViewVector = cameraTarget - cameraEye;
        cameraDistanceToTarget = gmtl::length(cameraViewVector);
        cameraViewDir = cameraViewVector;
        gmtl::normalize(cameraViewDir);
        gmtl::cross(cameraSideVector, cameraViewDir, cameraUpVector);
        gmtl::normalize(cameraSideVector);

        GL::lookAt(viewXform, cameraEye, cameraTarget, cameraUpVector);

        const real h = cameraHeight;
        const real w = aspect() * h;

        if (perspective)
            GL::frustum(projXform, -w, w, -h, h, 1.0f, 100000.0f);
        else
            GL::ortho(projXform, -w, w, -h, h, -100000.0f, 100000.0f);

        projViewXform = projXform * viewXform;
        gmtl::invertFull(inverseXform, projViewXform * modelXform);
        gmtl::invertFull(inverseCameraXform, projViewXform);

        if (autoViewUpdate && !autoViewUpdatePaused)
            updateAllFBOs();

        // Update ucs plane.
        real dirX = cameraViewDir[0];
        real dirZ = cameraViewDir[2];
        if (dirZ < -0.5f || 0.5f < dirZ)
            ucs = Constants::planeXY;
        else if (dirX < -0.5f || 0.5f < dirX)
            ucs = Constants::planeYZ;
        else
            ucs = Constants::planeXZ;
    }

    void updateModelXform()
    {
        Matrix trans;
        gmtl::setTrans(trans, modelTranslation);

        Matrix scale;
        gmtl::setScale(scale, Vector(modelScaleX, modelScaleY, modelScaleZ));

        modelXform = trans * scale;

        gmtl::invertFull(inverseXform, projViewXform * modelXform);

        if (autoViewUpdate && !autoViewUpdatePaused)
            updateAllFBOs();
    }

    void pushXforms()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(projXform.mData);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(viewXform.mData);
        glMultMatrixf(modelXform.mData);
    }

    void initStaticBuffers()
    {
        QVector<Vertex> vertices(4);
        vertices[0] = Vertex(0, 0, 0);
        vertices[1] = Vertex(100000.0f, 0, 0);
        vertices[2] = Vertex(0, 100000.0f, 0);
        vertices[3] = Vertex(0, 0, -100000.0f);
        staticVA->write(vertices);

        QVector<index> indices(6);
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 0;
        indices[3] = 2;
        indices[4] = 0;
        indices[5] = 3;
        staticIA->write(indices);
    }

    void drawStatic()
    {
        bool ok = staticVBO->bind();
        Q_ASSERT(ok);

        ok = staticIBO->bind();
        Q_ASSERT(ok);

        glVertexPointer(3, GL_FLOAT, 16, 0);

        glColor3f(0, 0, 0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};

} // namespace Internal
} // namespace GL

Viewport::Viewport(WidgetSplit *parentSplit)
    :   d(new ViewportPrivate(this, parentSplit))
{
    Q_CHECK_PTR(d);

    d->updateAllFBOs();
    d->widget->d->appendViewport(this);
}

Viewport::~Viewport()
{
    if (!d->widget->d->isBeingDestroyed)
        d->widget->d->removeViewport(this);

    delete d;  d = 0;
}

WidgetSplit *Viewport::parentSplit() const
{
    return d->parentSplit;
}

QColor Viewport::backgroundColor() const
{
    return d->backgroundColor;
}

void Viewport::setBackgroundColor(const QColor &color)
{
    if (d->backgroundColor == color)
        return;

    d->backgroundColor = color;
    d->backgroundColor.setAlphaF(1.0);

    d->updateFBO(BackgroundFBO);
}

QPoint Viewport::pos() const
{
    return d->parentSplit->pos();
}

QRect Viewport::rect() const
{
    return d->parentSplit->rect();
}

QSize Viewport::size() const
{
    return d->parentSplit->size();
}

int Viewport::width() const
{
    return d->parentSplit->width();
}

int Viewport::height() const
{
    return d->parentSplit->height();
}

void Viewport::resize(int width, int height)
{
    d->resizeFBOs(width, height);
}

void Viewport::updateAnimation()
{
    d->updateFBO(AnimationFBO);
}

void Viewport::updateView()
{
    d->updateAllFBOs();
}

bool Viewport::isAutomaticallyUpdatingView() const
{
    return d->autoViewUpdate;
}

void Viewport::setAutomaticViewUpdate(bool on)
{
    d->autoViewUpdate = on;
}

void Viewport::pauseAutomaticViewUpdate()
{
    d->autoViewUpdatePaused = true;
}

void Viewport::resumeAutomaticViewUpdate()
{
    d->autoViewUpdatePaused = false;
    d->updateAllFBOs();
}

bool Viewport::isPerspective() const
{
    return d->perspective;
}

void Viewport::setPerspective(bool perspective)
{
    d->perspective = perspective;
    d->updateCamera();
}

real Viewport::cameraHeight() const
{
    return d->cameraHeight;
}

void Viewport::setCameraHeight(GL::real height)
{
    d->cameraHeight = height;
    d->updateCamera();
}

void Viewport::setCameraTransform(const Point &eye, const Vector &up)
{
    d->cameraEye = eye;
    d->cameraUpVector = up;
    d->updateCamera();
}

void Viewport::setCameraTransform(const Point &eye, const Point &target, const Vector &up)
{
    d->cameraEye = eye;
    d->cameraTarget = target;
    d->cameraUpVector = up;
    d->updateCamera();
}

const Point &Viewport::cameraEye() const
{
    return d->cameraEye;
}

void Viewport::setCameraEye(const Point &eye)
{
    d->cameraEye = eye;
    d->updateCamera();
}

const Point &Viewport::cameraTarget() const
{
    return d->cameraTarget;
}

void Viewport::setCameraTarget(const Point &target)
{
    d->cameraTarget = target;
    d->updateCamera();
}

const Vector &Viewport::cameraUpVector() const
{
    return d->cameraUpVector;
}

void Viewport::setCameraUpVector(const Vector &up)
{
    d->cameraUpVector = up;
    d->updateCamera();
}

real Viewport::cameraDistanceToTarget() const
{
    return d->cameraDistanceToTarget;
}

const Vector &Viewport::cameraViewVector() const
{
    return d->cameraViewVector;
}

const Vector &Viewport::cameraViewDirection() const
{
    return d->cameraViewDir;
}

const Vector &Viewport::cameraSideVector() const
{
    return d->cameraSideVector;
}

void Viewport::setModelTransform(const Vector &translation, real scaleX, real scaleY, real scaleZ)
{
    d->modelTranslation = translation;
    d->modelScaleX = scaleX;
    d->modelScaleY = scaleY;
    d->modelScaleZ = scaleZ;
    d->updateModelXform();
}

void Viewport::setModelScale(real scaleX, real scaleY, real scaleZ)
{
    d->modelScaleX = scaleX;
    d->modelScaleY = scaleY;
    d->modelScaleZ = scaleZ;
    d->updateModelXform();
}

const Vector &Viewport::modelTranslation() const
{
    return d->modelTranslation;
}

void Viewport::setModelTranslation(const Vector &translation)
{
    d->modelTranslation = translation;
    d->updateModelXform();
}

real Viewport::modelScaleX() const
{
    return d->modelScaleX;
}

void Viewport::setModelScaleX(real scale)
{
    d->modelScaleX = scale;
    d->updateModelXform();
}

real Viewport::modelScaleY() const
{
    return d->modelScaleY;
}

void Viewport::setModelScaleY(real scale)
{
    d->modelScaleY = scale;
    d->updateModelXform();
}

real Viewport::modelScaleZ() const
{
    return d->modelScaleZ;
}

void Viewport::setModelScaleZ(real scale)
{
    d->modelScaleZ = scale;
    d->updateModelXform();
}

const Matrix &Viewport::projectionTransform() const
{
    return d->projXform;
}

const Matrix &Viewport::modelTransform() const
{
    return d->modelXform;
}

const Matrix &Viewport::viewTransform() const
{
    return d->viewXform;
}

const Matrix &Viewport::projectionViewTransform() const
{
    return d->projViewXform;
}

const Matrix &Viewport::inverseTransform() const
{
    return d->inverseXform;
}

const Matrix &Viewport::inverseCameraTransform() const
{
    return d->inverseCameraXform;
}

const Plane &Viewport::currentUcs() const
{
    return d->ucs;
}

Point Viewport::findPointOnCurrentUcs(const QPoint &pos) const
{
    return findPointOnPlane(pos, currentUcs());
}

Point Viewport::findPointOnPlane(const QPoint &pos, const Plane &plane) const
{
    const QSize size = this->size();
    const real w = size.width();
    const real h = size.height();
    const real posX = pos.x();
    const real posY = pos.y();

    // Calculate normalized device coordinates from 'pos'.
    const real x = (2.0f * posX / w) - 1.0f;
    const real y = -((2.0f * posY / h) - 1.0f);

    // Since the ray start and end point z coords are always 0 and -1, the
    // matrix multiplication can be optimized.

    // Instead of this ...
    //    Point startPt(x, y, 0);
    //    Point endPt(x, y, -1);
    //    startPt *= d->inverseCameraXform;
    //    endPt *= d->inverseCameraXform;

    // We optomize to this ...

    // Cache values common to start and end point transformations.
    const real *m = d->inverseCameraXform.mData;
    const real baseDenom = m[3] * x + m[7] * y + m[15];
    const real baseX = m[0] * x + m[4] * y + m[12];
    const real baseY = m[1] * x + m[5] * y + m[13];
    const real baseZ = m[2] * x + m[6] * y + m[14];

    // Calculate ray's start point.
    const real startDenom = 1.0f / baseDenom;
    if (startDenom == 0.0f) {
        Q_ASSERT(false && "Can't calculate ray start point.");
        return Point();
    }
    const Point startPt(
        startDenom * baseX,
        startDenom * baseY,
        startDenom * baseZ);

    // Calculate ray's end point.
    const real endDenom = 1.0f / (baseDenom - m[11]);
    if (endDenom == 0.0f) {
        Q_ASSERT(false && "Can't calculate ray end point.");
        return Point();
    }
    const Point endPt(
        endDenom * (baseX - m[8]),
        endDenom * (baseY - m[9]),
        endDenom * (baseZ - m[10]));

    // Find intersection of ray and plane.
    real t;
    Ray ray(startPt, startPt - endPt);
    gmtl::intersect(plane, ray, t);
    Point pt = ray.mOrigin + ray.mDir * t;
    pt[0] = -pt[0];
    return pt;
}

void Viewport::paintGL()
{
    const Widget *widget = d->widget;
    const QRect rect = this->rect();

    const real left = rect.left();
    const real bottom = widget->height() - rect.bottom() - 1;
    const real width = rect.width();
    const real height = rect.height();
    Q_ASSERT(0 < width);
    Q_ASSERT(0 < height);

    glViewport(left, bottom, width, height);

    const WidgetPrivate *widget_d = widget->d;
    widget_d->shaderProgram->setUniformValue(widget_d->screenOriginId, left, bottom);
    widget_d->shaderProgram->setUniformValue(widget_d->screenSizeId, width, height);

    foreach (const GLuint &id, d->textureIds) {
        if (id == 0)
            continue;
        glBindTexture(GL_TEXTURE_2D, id);
        glCallList(widget_d->displayListId);
    }
}
