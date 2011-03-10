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

    void setCameraVectors(const QVector3D &position, const QVector3D &target, const QVector3D &upVector);
    const QVector3D &cameraTarget() const;
    void setCameraTarget(const QVector3D &target);
    const QVector3D &cameraPosition() const;
    void setCameraPosition(const QVector3D &position);
    const QVector3D &cameraUpVector() const;
    void setCameraUpVector(const QVector3D &upVector);
    bool isPerspective() const;
    void setPerspective(bool perspective);

    const QMatrix4x4 &screenTransform() const;
    const QMatrix4x4 &projectionTransform() const;
    const QMatrix4x4 &viewTransform() const;
    const QMatrix4x4 &worldTransform() const;

protected:
    virtual void paintGL();

private:
    Internal::GLViewportPrivate *d;
    Q_DISABLE_COPY(GLViewport)

    friend class GLWidget;
};

} // namespace GLEditor

#endif // GLVIEWPORT_H
