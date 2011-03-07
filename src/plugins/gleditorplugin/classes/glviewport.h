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
class GLWidgetSplit;

namespace Internal {
class GLViewportPrivate;
} // namespace Internal

class GLEDITOR_EXPORT GLViewport : public QObject
{
    Q_OBJECT

public:
    GLViewport(GLWidgetSplit *split);
    virtual ~GLViewport();

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QPoint pos() const;
    QRect rect() const;
    QSize size() const;
    int width() const;
    int height() const;
    void resize(int width, int height);

public slots:
    void updateAnimation();

protected:
    virtual void paintGL();

private:
    Internal::GLViewportPrivate *d;
    Q_DISABLE_COPY(GLViewport)

    friend class GLWidget;
    friend class GLWidgetSplit;
};

} // namespace GLEditor

#endif // GLVIEWPORT_H
