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

#ifndef GLWIDGET_P_H
#define GLWIDGET_P_H

#include <QtCore/QElapsedTimer>
#include <QtCore/qlist.h>

#include <QtGui/QVector3D>

QT_BEGIN_NAMESPACE

class QElapsedTimer;

class QGLShader;
class QGLShaderProgram;

QT_END_NAMESPACE

namespace GLScene {

class IGLScene;

} // namespace GLScene

namespace GLEditor {

class GLViewport;
class GLWidget;
class GLWidgetSplit;

namespace Internal {

class GLWidgetPrivate
{
public:
    GLWidget *q;
    GLScene::IGLScene *scene;
    GLWidgetSplit *mainSplit;
    GLWidgetSplit *currentSplit;
    quint32 displayListId;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;
    int screenOriginId;
    int screenSizeId;
    GLWidgetSplit *draggingSplit;
    QPoint dragStartScreenPosition;
    GLViewport *draggingViewport;
    QVector3D dragStartCameraPosition;
    QVector3D dragStartCameraTarget;
    bool isPanning;
    bool isRotating;
    QElapsedTimer elapsedTime;
    bool animating;
    bool isBeingDestroyed;

    QList<GLViewport*> viewports;

    GLWidgetPrivate(GLWidget *q);
    ~GLWidgetPrivate();

    void initialize();

    void appendViewport(GLViewport *viewport);
    void removeViewport(GLViewport* viewport);

    GLViewport *viewportAtPosition(const QPoint &position) const;

private:
    void initializeScene();
    void initializeSplits();
    void initializeShaders();
    void initializeDisplayLists();
};

} // namespace Internal
} // namespace GLEditor

#endif // GLWIDGET_P_H