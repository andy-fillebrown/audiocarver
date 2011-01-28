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
        mainSplit = 0;
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
        mainSplit = new GLWidgetSplit(q, q->size());
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

    void draw()
    {
//        qglPushState();
//        viewportLeft->update();
//        viewportRight->update();
//        Q_CHECK(shaderProgram->bind());

//        glClearColor(0, 0, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT);
//        glEnable(GL_BLEND);
//        glEnable(GL_CULL_FACE);
//        glDisable(GL_DEPTH_TEST);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

//        const QSize cw = q->size();
//        const int modW = cw.width() % 2;
//        const int modH = cw.height() % 2;

//        const QSize vpL = viewportLeft->size();
//        const int vpL_w = vpL.width() + modW;
//        const int vpL_h = vpL.height() + modH;
//        glViewport(0, 0, vpL_w, vpL_h);
//        shaderProgram->setUniformValue(screenOriginId, 0, 0);
//        shaderProgram->setUniformValue(screenSizeId, vpL_w, vpL_h);
//        glBindTexture(GL_TEXTURE_2D, viewportLeft->staticTextureId());
//        glCallList(displayListId);
//        glBindTexture(GL_TEXTURE_2D, viewportLeft->animatedTextureId());
//        glCallList(displayListId);

//        const QSize vpR = viewportRight->size();
//        const int vpR_w = vpR.width() + modW;
//        const int vpR_h = vpR.height() + modH;
//        glViewport(vpL_w, 0, vpR_w, vpR_h);
//        shaderProgram->setUniformValue(screenOriginId, vpL_w, 0);
//        shaderProgram->setUniformValue(screenSizeId, vpR_w, vpR_h);
//        glBindTexture(GL_TEXTURE_2D, viewportRight->staticTextureId());
//        glCallList(displayListId);
//        glBindTexture(GL_TEXTURE_2D, viewportRight->animatedTextureId());
//        glCallList(displayListId);

//        shaderProgram->release();
//        qglPopState();
//        Q_CHECK_GLERROR;
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
}

void GLWidget::splitVertical()
{
    currentSplit()->splitVertical();
}

void GLWidget::removeCurrentSplit()
{
    if (d->currentSplit == d->mainSplit)
        return;
    d->currentSplit->removeSplit();
}

void GLWidget::removeAllSplits()
{
    d->mainSplit->removeSplit();
}

QMutex *GLWidget::glDrawMutex() const
{
    return d->drawMutex;
}
