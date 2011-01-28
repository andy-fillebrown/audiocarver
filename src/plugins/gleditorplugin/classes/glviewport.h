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

#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <gleditorplugin/gleditor_global.h>

#include <utils3d/utils3d_global.h>

namespace GLEditor {
class GLWidget;

namespace Internal {
class GLViewportPrivate;
} // namespace Internal

class GLEDITOR_EXPORT GLViewport : public QObject
{
    Q_OBJECT

public:
    GLViewport(GLWidget *widget, const QSize &size);
    GLViewport(GLWidget *widget, int width, int height);
    virtual ~GLViewport();

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    void setBackgroundColor(GLfloat red, GLfloat blue, GLfloat green, GLfloat alpha = 1.0f);

    QSize size() const;
    int width() const;
    int height() const;
    void resize(const QSize &size);
    void resize(int width, int height);

    const QList<GLuint> &textureIds() const;

public slots:
    void update();

private:
    Internal::GLViewportPrivate *d;
};

} // namespace GLEditor

#endif // GLVIEWPORT_H
