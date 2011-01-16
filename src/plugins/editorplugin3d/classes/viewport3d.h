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

#ifndef VIEWPORT3D_H
#define VIEWPORT3D_H

#include <editorplugin3d/editor3d_global.h>

#include <utils3d/utils3d_global.h>

#include <QtCore/QObject>
#include <QtCore/QSize>

class QGLFramebufferObject;

namespace Editor3D {

class CentralWidget3D;

namespace Internal {

class Viewport3DPrivate;

} // namespace Internal

class EDITOR3D_EXPORT Viewport3D : public QObject
{
    Q_OBJECT

public:
    Viewport3D(CentralWidget3D *centralWidget, int w, int h);
    virtual ~Viewport3D();

    CentralWidget3D *centralWidget() const;
    QSize size() const;

    void setBackgroundColor(const QColor &color);
    void setRotation(float rotation);
    GLuint textureId() const;

public slots:
    void update();
    void startCameraDrag(const QPoint &startPoint);

signals:
    void cameraDragFinished();

protected:
    friend class CentralWidget3D;
    void resize(int w, int h);

private:
    Internal::Viewport3DPrivate *d;
};

} // namespace Editor3D

#endif // VIEWPORT3D_H
