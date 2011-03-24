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

#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <gleditorplugin/gleditor_global.h>

#include <QtOpenGL/QGLWidget>

namespace GL {
namespace Internal {

class WidgetPrivate;

} // namespace Internal

class BehaviorSettings;
class DisplaySettings;

class IScene;

class Viewport;
class WidgetSplit;

class GLEDITOR_EXPORT Widget : public QGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    virtual ~Widget();

    IScene *currentScene() const;
    void setCurrentScene(IScene *scene);

    WidgetSplit *currentSplit() const;
    void setCurrentSplit(WidgetSplit *split);

    Viewport *currentViewport() const;
    void setCurrentViewport(Viewport *viewport);

    void setAnimating(bool animating = true);
    bool isAnimating() const;
    qreal animationTime() const;

public slots:
    void splitHorizontal();
    void splitVertical();
    void removeCurrentSplit();
    void removeAllSplits();

    void updateBehaviorSettings(const BehaviorSettings &previousSettings);
    void updateDisplaySettings(const DisplaySettings &previousSettings);

    virtual void animateGL();

protected:
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    Internal::WidgetPrivate *d;
    Q_DISABLE_COPY(Widget)

    friend class Viewport;
};

} // namespace GL

#endif // GL_WIDGET_H
