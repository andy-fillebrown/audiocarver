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

#include "glwidget.h"
#include "glwidgetsplit.h"
#include "glviewport.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

#include <QtCore/QMutex>

using namespace GLEditor;

namespace GLEditor {
namespace Internal {

class GLWidgetPrivate
{
public:
    GLWidget *q;
    QMutex *drawMutex;
    GLWidgetSplit *mainSplit;
    GLWidgetSplit *currentSplit;
    GLuint displayListId;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;
    int screenOriginId;
    int screenSizeId;

    GLWidgetPrivate(GLWidget *q)
        :   q(q)
        ,   drawMutex(new QMutex)
        ,   mainSplit(0)
        ,   currentSplit(0)
        ,   displayListId(0)
        ,   vertexShader(0)
        ,   fragmentShader(0)
        ,   shaderProgram(0)
        ,   screenOriginId(-1)
        ,   screenSizeId(-1)
    {
        Q_CHECK_PTR(drawMutex);
    }

    ~GLWidgetPrivate()
    {
        // Make context current for glDeleteLists.
        q->makeCurrent();
        Q_ASSERT(q->isValid());

        screenSizeId = -1;
        screenOriginId = -1;
        shaderProgram = 0;
        fragmentShader = 0;
        vertexShader = 0;
        glDeleteLists(displayListId, 1);  displayListId = 0;
        currentSplit = 0;
        delete mainSplit;  mainSplit = 0;
        delete drawMutex;  drawMutex = 0;
        q = 0;
    }

    void initialize()
    {
        initializeSplits();
        initializeShaders();
        initializeDisplayLists();
    }

    void initializeSplits()
    {
        mainSplit = new GLWidgetSplit(q);
        Q_CHECK_PTR(mainSplit);

        currentSplit = mainSplit;
    }

    void initializeShaders()
    {
        Q_ASSERT(q->isValid());

        vertexShader = new QGLShader(QGLShader::Vertex, q);
        Q_CHECK_PTR(vertexShader);
        Q_CHECK(vertexShader->compileSourceFile(":/gleditor/shaders/glwidget_vertex.glsl"));
        if (!vertexShader->isCompiled())
            qDebug() << vertexShader->log();

        fragmentShader = new QGLShader(QGLShader::Fragment, q);
        Q_CHECK_PTR(fragmentShader);
        Q_CHECK(fragmentShader->compileSourceFile(":/gleditor/shaders/glwidget_fragment.glsl"));
        if (!fragmentShader->isCompiled())
            qDebug() << fragmentShader->log();

        shaderProgram = new QGLShaderProgram(q);
        Q_CHECK_PTR(shaderProgram);
        Q_CHECK(shaderProgram->addShader(vertexShader));
        Q_CHECK(shaderProgram->addShader(fragmentShader));
        Q_CHECK(shaderProgram->link());

        screenOriginId = shaderProgram->uniformLocation("screenOrigin");
        screenSizeId = shaderProgram->uniformLocation("screenSize");
        Q_ASSERT(screenOriginId != -1);
        Q_ASSERT(screenSizeId != -1);
        Q_CHECK_GLERROR;
    }

    void initializeDisplayLists()
    {
        displayListId = glGenLists(1);
        glNewList(displayListId, GL_COMPILE);
        glBegin(GL_TRIANGLES);
        glVertex2f(-2.0, -1.0);
        glVertex2f(2.0, -1.0);
        glVertex2f(0.0, 4.0);
        glEnd();
        glEndList();
        Q_CHECK_GLERROR;
    }
};

} // namespace Internal
} // namespace Editor3D

GLWidget::GLWidget(QWidget *parent)
    :   QGLWidget(parent)
    ,   d(new Internal::GLWidgetPrivate(this))
{
    Q_CHECK_PTR(d);

    makeCurrent();
    Q_CHECK(isValid());

    d->initialize();
}

GLWidget::~GLWidget()
{
    makeCurrent();
    delete d;  d = 0;
}

GLWidgetSplit *GLWidget::currentSplit() const
{
    return d->currentSplit;
}

void GLWidget::setCurrentSplit(GLWidgetSplit *split)
{
    d->currentSplit = split;
}

void GLWidget::splitHorizontal()
{
    currentSplit()->splitHorizontal();
    d->mainSplit->resize();
    updateGL();
}

void GLWidget::splitVertical()
{
    currentSplit()->splitVertical();
    d->mainSplit->resize();
    updateGL();
}

void GLWidget::removeCurrentSplit()
{
    if (d->currentSplit == d->mainSplit)
        return;
    d->currentSplit->removeSplit();
    d->mainSplit->resize();
    updateGL();
}

void GLWidget::removeAllSplits()
{
    d->mainSplit->removeSplit();
    d->mainSplit->resize();
    updateGL();
}

QMutex *GLWidget::glDrawMutex() const
{
    return d->drawMutex;
}

void GLWidget::drawViewport(GLViewport *viewport)
{
    QRect vp = viewport->rect();
    Q_ASSERT(0 < vp.width());
    Q_ASSERT(0 < vp.height());
    glViewport(vp.left(), vp.top(), vp.width(), vp.height());
    d->shaderProgram->setUniformValue(d->screenOriginId, vp.left(), vp.top());
    d->shaderProgram->setUniformValue(d->screenSizeId, vp.width(), vp.height());

    const QList<GLuint> &textureIds = viewport->textureIds();
    foreach (const GLuint &id, textureIds) {
        glBindTexture(GL_TEXTURE_2D, id);
        glCallList(d->displayListId);
    }
}

void GLWidget::paintGL()
{
    qglPushState();
    Q_CHECK(d->shaderProgram->bind());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    d->mainSplit->draw();

    d->shaderProgram->release();
    Q_CHECK_GLERROR;
    qglPopState();
}

void GLWidget::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
    d->mainSplit->resize();
}
