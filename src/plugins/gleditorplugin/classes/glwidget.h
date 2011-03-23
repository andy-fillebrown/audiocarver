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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <gleditorplugin/gleditor_global.h>

#include <QtOpenGL/QGLWidget>

namespace GLScene {

class IGLScene;

} // namespace GLScene

namespace GLEditor {
namespace Internal {

class GLWidgetPrivate;

} // namespace Internal

class GLViewport;
class GLWidgetSplit;

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

    void updateBehaviorSettings();
    void updateDisplaySettings();

    virtual void animateGL();

protected:
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    Internal::GLWidgetPrivate *d;
    Q_DISABLE_COPY(GLWidget)

    friend class GLEditorSettings;
    friend class GLViewport;
};

} // namespace GLEditor

#endif // GLWIDGET_H
