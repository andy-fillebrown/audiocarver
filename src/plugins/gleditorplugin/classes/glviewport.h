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

#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <gleditorplugin/gleditor_global.h>

#include <utils3d/utils3d_global.h>

namespace GLEditor {
namespace Internal {

class GLViewportPrivate;

} // namespace Internal

class GLWidgetSplit;

class GLEDITOR_EXPORT GLViewport : public QObject
{
    Q_OBJECT

public:
    GLViewport(GLWidgetSplit *parentSplit);
    virtual ~GLViewport();

    GLWidgetSplit *parentSplit() const;

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

    GL::real cameraHeight() const;
    void setCameraHeight(GL::real height);

    void setCameraMatrix(const GL::Point &position, const GL::Point &target, const GL::Vector &upVector);
    const GL::Point &cameraPosition() const;
    void setCameraPosition(const GL::Point &position);
    const GL::Point &cameraTarget() const;
    void setCameraTarget(const GL::Point &target);
    const GL::Vector &cameraUpVector() const;
    void setCameraUpVector(const GL::Vector &upVector);

    GL::real cameraDistanceToTarget() const;
    const GL::Vector &cameraViewVector() const;
    const GL::Vector &cameraViewDirection() const;
    const GL::Vector &cameraSideVector() const;

    void setModelMatrix(const GL::Vector &translation, GL::real scaleX, GL::real scaleY, GL::real scaleZ);
    void setModelScale(GL::real scaleX, GL::real scaleY, GL::real scaleZ);
    const GL::Vector &modelTranslation() const;
    void setModelTranslation(const GL::Vector &translation);
    GL::real modelScaleX() const;
    void setModelScaleX(GL::real scale);
    GL::real modelScaleY() const;
    void setModelScaleY(GL::real scale);
    GL::real modelScaleZ() const;
    void setModelScaleZ(GL::real scale);

    const GL::Matrix &projXform() const;
    const GL::Matrix &modelXform() const;
    const GL::Matrix &viewXform() const;

    const GL::Plane &currentUcs() const;
    GL::Point findPointOnUcs(const QPoint &screenPos) const;
    GL::Point findPointOnPlane(const QPoint &screenPos, const GL::Plane &plane) const;

protected:
    virtual void paintGL();

private:
    Internal::GLViewportPrivate *d;
    Q_DISABLE_COPY(GLViewport)

    friend class GLWidget;
};

} // namespace GLEditor

#endif // GLVIEWPORT_H
