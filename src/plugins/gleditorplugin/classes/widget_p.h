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

#ifndef GL_WIDGET_P_H
#define GL_WIDGET_P_H

#include <utils3d/utils3d_global.h>

#include <QtCore/QElapsedTimer>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE

class QElapsedTimer;

class QGLShader;
class QGLShaderProgram;

QT_END_NAMESPACE

namespace GL {

class BehaviorSettings;
class DisplaySettings;

class IScene;

class Viewport;
class Widget;
class WidgetSplit;

namespace Internal {

class WidgetPrivate
{
public:
    Widget *q;
    IScene *scene;
    WidgetSplit *mainSplit;
    WidgetSplit *currentSplit;

    quint32 displayListId;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;
    int screenOriginId;
    int screenSizeId;

    WidgetSplit *draggingSplit;
    QPoint dragStartScreenPosition;
    Viewport *draggingViewport;
    QPoint prevDragPos;
    bool isPanning;
    bool isRotating;

    QElapsedTimer elapsedTime;
    qint64 prevFrameTime;
    bool animating;

    bool isBeingDestroyed;

    QList<Viewport*> viewports;

    BehaviorSettings *behaviorSettings;
    DisplaySettings *displaySettings;

    WidgetPrivate(Widget *q);
    ~WidgetPrivate();

    void initialize();

    void appendViewport(Viewport *viewport);
    void removeViewport(Viewport* viewport);

    Viewport *viewportAtPosition(const QPoint &position) const;

private:
    void initializeScene();
    void initializeSplits();
    void initializeShaders();
    void initializeDisplayLists();
};

} // namespace Internal
} // namespace GL

#endif // GL_WIDGET_P_H
