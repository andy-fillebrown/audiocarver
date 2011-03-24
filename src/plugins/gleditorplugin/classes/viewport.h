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

#ifndef GL_VIEWPORT_H
#define GL_VIEWPORT_H

#include <gleditorplugin/gleditor_global.h>

#include <glutils/glutils_global.h>

namespace GL {
namespace Internal {

class ViewportPrivate;

} // namespace Internal

class WidgetSplit;

class GLEDITOR_EXPORT Viewport : public QObject
{
    Q_OBJECT

public:
    Viewport(WidgetSplit *parentSplit);
    virtual ~Viewport();

    WidgetSplit *parentSplit() const;

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QPoint pos() const;
    QRect rect() const;
    QSize size() const;
    int width() const;
    int height() const;
    void resize(int width, int height);

    void updateAnimation();
    void updateView();

    bool isViewAutomaticallyUpdated() const;
    void setViewAutomaticUpdate(bool automatic);
    void pushViewAutomaticUpdate();
    void popViewAutomaticUpdate();

    bool isPerspective() const;
    void setPerspective(bool perspective);

    real cameraHeight() const;
    void setCameraHeight(real height);

    void setCameraMatrix(const Point &position, const Point &target, const Vector &upVector);
    const Point &cameraPosition() const;
    void setCameraPosition(const Point &position);
    const Point &cameraTarget() const;
    void setCameraTarget(const Point &target);
    const Vector &cameraUpVector() const;
    void setCameraUpVector(const Vector &upVector);

    real cameraDistanceToTarget() const;
    const Vector &cameraViewVector() const;
    const Vector &cameraViewDirection() const;
    const Vector &cameraSideVector() const;

    void setModelMatrix(const Vector &translation, real scaleX, real scaleY, real scaleZ);
    void setModelScale(real scaleX, real scaleY, real scaleZ);
    const Vector &modelTranslation() const;
    void setModelTranslation(const Vector &translation);
    real modelScaleX() const;
    void setModelScaleX(real scale);
    real modelScaleY() const;
    void setModelScaleY(real scale);
    real modelScaleZ() const;
    void setModelScaleZ(real scale);

    const Matrix &projXform() const;
    const Matrix &modelXform() const;
    const Matrix &viewXform() const;

    const Matrix &projViewXform() const;
    const Matrix &inverseXform() const;
    const Matrix &inverseCameraXform() const;

    const Plane &currentUcs() const;
    Point findPointOnUcs(const QPoint &screenPos) const;
    Point findPointOnPlane(const QPoint &screenPos, const Plane &plane) const;

protected:
    virtual void paintGL();

private:
    Internal::ViewportPrivate *d;
    Q_DISABLE_COPY(Viewport)

    friend class Widget;
};

} // namespace GL

#endif // GL_VIEWPORT_H
