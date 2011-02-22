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

namespace GLScene {
class IGLScene;
} // namespace GLDatabase

namespace GLEditor {
class GLViewport;
class GLWidgetSplit;

namespace Internal {
class GLWidgetDrawThread;
class GLWidgetPrivate;
} // namespace Internal

class GLEDITOR_EXPORT GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    GLScene::IGLScene *currentScene() const;
    void setCurrentScene(GLScene::IGLScene *scene);

    GLWidgetSplit *currentSplit() const;
    void setCurrentSplit(GLWidgetSplit *split);

    GLViewport *currentViewport() const;
    void setCurrentViewport(GLViewport *viewport);

    void setAnimating(bool animating = true);
    bool isAnimating() const;
    qreal animationTime() const;

public slots:
    void splitHorizontal();
    void splitVertical();
    void removeCurrentSplit();
    void removeAllSplits();

    void animateGL();

protected:
    friend class GLViewport;
    friend class Internal::GLWidgetDrawThread;

    virtual void drawViewport(GLViewport *viewport);

    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    Internal::GLWidgetPrivate *d;
};

} // namespace GLEditor

#endif // GLWIDGET_H
