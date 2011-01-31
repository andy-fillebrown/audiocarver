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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <gleditorplugin/gleditor_global.h>

#include <QtOpenGL/QGLWidget>

QT_BEGIN_NAMESPACE
class QMutex;
QT_END_NAMESPACE

namespace GLEditor {
class GLViewport;
class GLWidgetSplit;

namespace Internal {
class GLWidgetPrivate;
} // namespace Internal

class GLEDITOR_EXPORT GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    GLWidgetSplit *currentSplit() const;
    void setCurrentSplit(GLWidgetSplit *split);

public slots:
    void splitHorizontal();
    void splitVertical();
    void removeCurrentSplit();
    void removeAllSplits();

protected:
    friend class GLViewport;
    virtual void drawViewport(GLViewport *viewport);
    QMutex *glDrawMutex() const;

    virtual void glDraw();
    virtual void glResize(int width, int height);

private:
    Internal::GLWidgetPrivate *d;
};

} // namespace GLEditor

#endif // GLWIDGET_H