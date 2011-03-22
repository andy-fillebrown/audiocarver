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

    bool viewAutoUpdate;
    bool viewAutoUpdatePushed;

    bool perspective;
    Point cameraPosition;
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
        ,   viewAutoUpdate(true)
        ,   viewAutoUpdatePushed(false)
        ,   perspective(false)
        ,   cameraPosition(0.0f, 0.0f, -10.0f)
        ,   cameraTarget(0.0f, 0.0f, 0.0f)
        ,   cameraUpVector(GL::yAxis)
        ,   cameraDistanceToTarget(qAbs(cameraPosition[2]))
        ,   cameraHeight(10.0f)
        ,   cameraViewVector(cameraTarget - cameraPosition)
        ,   cameraViewDir(0.0f, 0.0f, 1.0f)
        ,   cameraSideVector(GL::xAxis)
        ,   modelTranslation(0.0f, 0.0f, 0.0f)
        ,   modelScaleX(1.0f)
        ,   modelScaleY(1.0f)
        ,   modelScaleZ(1.0f)
        ,   ucs(GL::xyPlane)
    {
        Q_ASSERT(widget);

        initializeGLFunctions(widget->context());
        initializeFBOs(parentSplit->width(), parentSplit->height());

        updateCamera();
        updateModelXform();
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

        const QSize size = parentSplit->size();
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
        cameraViewVector = cameraTarget - cameraPosition;
        cameraDistanceToTarget = gmtl::length(cameraViewVector);
        cameraViewDir = cameraViewVector;
        gmtl::normalize(cameraViewDir);
        gmtl::cross(cameraSideVector, cameraViewDir, cameraUpVector);
        gmtl::normalize(cameraSideVector);

        GL::lookAt(viewXform, cameraPosition, cameraTarget, cameraUpVector);

        const real aspect = this->aspect();
        const real h = cameraHeight;
        const real w = aspect * h;

        if (perspective)
            GL::frustum(projXform, -w, w, -h, h, 1.0f, 100000.0f);
        else
            GL::ortho(projXform, -w, w, -h, h, -100000.0f, 100000.0f);

        projViewXform = projXform * viewXform;
        gmtl::invertFull(inverseXform, projViewXform * modelXform);
        gmtl::invertFull(inverseCameraXform, projViewXform);

        if (viewAutoUpdate && !viewAutoUpdatePushed)
            updateAllFBOs();

        // Update ucs plane.
        real dirX = cameraViewDir[0];
        real dirZ = cameraViewDir[2];
        if (dirZ < -0.5f || 0.5f < dirZ)
            ucs = GL::xyPlane;
        else if (dirX < -0.5f || 0.5f < dirX)
            ucs = GL::yzPlane;
        else
            ucs = GL::xzPlane;
    }

    void updateModelXform()
    {
        Matrix trans;
        gmtl::setTrans(trans, modelTranslation);

        Matrix scale;
        gmtl::setScale(scale, Vector(modelScaleX, modelScaleY, modelScaleZ));

        modelXform = trans * scale;

        gmtl::invertFull(inverseXform, projViewXform * modelXform);

        if (viewAutoUpdate && !viewAutoUpdatePushed)
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

void GLViewport::updateView()
{
    d->updateAllFBOs();
}

bool GLViewport::isViewAutomaticallyUpdated() const
{
    return d->viewAutoUpdate;
}

void GLViewport::setViewAutomaticUpdate(bool automatic)
{
    d->viewAutoUpdate = automatic;
}

void GLViewport::pushViewAutomaticUpdate()
{
    d->viewAutoUpdatePushed = true;
}

void GLViewport::popViewAutomaticUpdate()
{
    d->viewAutoUpdatePushed = false;
    d->updateAllFBOs();
}

bool GLViewport::isPerspective() const
{
    return d->perspective;
}

void GLViewport::setPerspective(bool perspective)
{
    d->perspective = perspective;
    d->updateCamera();
}

real GLViewport::cameraHeight() const
{
    return d->cameraHeight;
}

void GLViewport::setCameraHeight(GL::real height)
{
    d->cameraHeight = height;
    d->updateCamera();
}

void GLViewport::setCameraMatrix(const Point &position, const Point &target, const Vector &upVector)
{
    d->cameraPosition = position;
    d->cameraTarget = target;
    d->cameraUpVector = upVector;
    d->updateCamera();
}

const Point &GLViewport::cameraPosition() const
{
    return d->cameraPosition;
}

void GLViewport::setCameraPosition(const Point &position)
{
    d->cameraPosition = position;
    d->updateCamera();
}

const Point &GLViewport::cameraTarget() const
{
    return d->cameraTarget;
}

void GLViewport::setCameraTarget(const Point &target)
{
    d->cameraTarget = target;
    d->updateCamera();
}

const Vector &GLViewport::cameraUpVector() const
{
    return d->cameraUpVector;
}

void GLViewport::setCameraUpVector(const Vector &upVector)
{
    d->cameraUpVector = upVector;
    d->updateCamera();
}

real GLViewport::cameraDistanceToTarget() const
{
    return d->cameraDistanceToTarget;
}

const Vector &GLViewport::cameraViewVector() const
{
    return d->cameraViewVector;
}

const Vector &GLViewport::cameraViewDirection() const
{
    return d->cameraViewDir;
}

const Vector &GLViewport::cameraSideVector() const
{
    return d->cameraSideVector;
}

void GLViewport::setModelMatrix(const GL::Vector &translation, GL::real scaleX, GL::real scaleY, GL::real scaleZ)
{
    d->updateModelXform();
}

void GLViewport::setModelScale(GL::real scaleX, GL::real scaleY, GL::real scaleZ)
{
    d->updateModelXform();
}

const Vector &GLViewport::modelTranslation() const
{
    return d->modelTranslation;
}

void GLViewport::setModelTranslation(const GL::Vector &translation)
{
    d->modelTranslation = translation;
    d->updateModelXform();
}

real GLViewport::modelScaleX() const
{
    return d->modelScaleX;
}

void GLViewport::setModelScaleX(GL::real scale)
{
    d->modelScaleX = scale;
    d->updateModelXform();
}

real GLViewport::modelScaleY() const
{
    return d->modelScaleY;
}

void GLViewport::setModelScaleY(GL::real scale)
{
    d->modelScaleY = scale;
    d->updateModelXform();
}

real GLViewport::modelScaleZ() const
{
    return d->modelScaleZ;
}

void GLViewport::setModelScaleZ(GL::real scale)
{
    d->modelScaleZ = scale;
    d->updateModelXform();
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

const Matrix &GLViewport::projViewXform() const
{
    return d->projViewXform;
}

const Matrix &GLViewport::inverseXform() const
{
    return d->inverseXform;
}

const Matrix &GLViewport::inverseCameraXform() const
{
    return d->inverseCameraXform;
}

const Plane &GLViewport::currentUcs() const
{
    return d->ucs;
}

Point GLViewport::findPointOnUcs(const QPoint &screenPos) const
{
    return findPointOnPlane(screenPos, currentUcs());
}

Point GLViewport::findPointOnPlane(const QPoint &screenPos, const GL::Plane &plane) const
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
    const real endDenom = 1.0f / (baseDenom + m[11]);
    if (endDenom == 0.0f) {
        Q_ASSERT(false && "Can't calculate ray end point.");
        return Point();
    }
    const Point endPt(
        endDenom * (baseX + m[8]),
        endDenom * (baseY + m[9]),
        endDenom * (baseZ + m[10]));

    // Find intersection of ray and plane.
    real t;
    Ray ray(startPt, endPt - startPt);
    gmtl::intersect(plane, ray, t);
    Point pt = ray.mOrigin + ray.mDir * t;
    pt[0] = -pt[0];
    return pt;
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
