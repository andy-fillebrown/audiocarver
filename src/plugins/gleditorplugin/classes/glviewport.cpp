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

#include "glviewport.h"

#include "glwidget.h"
#include "glwidgetsplit.h"

#include <utils3d/utils3d_global.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLFunctions>

class Testing : protected QGLFunctions
{
public:
    GLuint staticDisplayListId;
    GLuint animatedDisplayListId;
    float rotation;

    Testing()
        :   staticDisplayListId(-1)
        ,   animatedDisplayListId(-1)
        ,   rotation(0)
    {
        initializeGLFunctions();
    }

    ~Testing()
    {
        glDeleteLists(animatedDisplayListId, 1);  animatedDisplayListId = -1;
        glDeleteLists(staticDisplayListId, 1);  staticDisplayListId = -1;
        rotation = 0;
    }

    void initDisplayLists()
    {
        staticDisplayListId = glGenLists(1);
        glNewList(staticDisplayListId, GL_COMPILE);
        drawStaticGeometry();
        glEndList();

        Q_CHECK_GLERROR;

        animatedDisplayListId = glGenLists(1);
        glNewList(animatedDisplayListId, GL_COMPILE);
        drawAnimatedGeometry();
        glEndList();

        Q_CHECK_GLERROR;
    }

    void drawStaticGeometry()
    {
        static const GLfloat x = 1.0f;
        static const GLfloat y = 1.0f;
        static const GLfloat S1[3] = { x, y, 0.0 };
        static const GLfloat S2[3] = { x, -y, 0.0 };
        static const GLfloat S3[3] = { -x, y, 0.0 };
        static const GLfloat S4[3] = { -x, -y, 0.0 };
        static const GLfloat * const coordsS[2][3] = {
            { S2, S1, S3 }, { S3, S4, S2 }
        };
        glBegin(GL_TRIANGLES);
        glColor4f(0.5, 0.5, 0.5, 0.5);
        for (int i = 0;  i < 2;  ++i) {
            for (int j = 0;  j < 3;  ++j)
                glVertex3f(coordsS[i][j][0], coordsS[i][j][1], coordsS[i][j][2]);
        }
        glEnd();

        Q_CHECK_GLERROR;
    }

    void drawAnimatedGeometry()
    {
        static const GLfloat A1[3] = { 0.0, -1.0, 2.0 };
        static const GLfloat A2[3] = { 1.73205081, -1.0, -1.0 };
        static const GLfloat A3[3] = { -1.73205081, -1.0, -1.0 };
        static const GLfloat A4[3] = { 0.0, 2.0, 0.0 };
        static const GLfloat * const coordsA[4][3] = {
            { A1, A2, A3 }, { A1, A3, A4 }, { A1, A4, A2 }, { A2, A4, A3 }
        };
        static const GLfloat faceColorsA[][3] = {
            { 1, 1, 1 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }
        };
        glBegin(GL_TRIANGLES);
        for (int i = 0;  i < 4;  ++i) {
            glColor4f(faceColorsA[i][0], faceColorsA[i][1], faceColorsA[i][2], 0.5f);
            for (int j = 0; j < 3; ++j)
                glVertex3f(coordsA[i][j][0], coordsA[i][j][1], coordsA[i][j][2]);
        }
        glEnd();

        Q_CHECK_GLERROR;
    }

    void drawStaticFBO(GLfloat aspect)
    {
        glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
        glTranslatef(0.0, 0.0, -10.0);
        glCallList(staticDisplayListId);
    }

    void drawAnimatedFBO(GLfloat aspect)
    {
        glFrustum(-aspect, aspect, -1.0, 1.0, 4.0, 15.0);
        glTranslatef(0.0, 0.0, -10.0);
        glRotatef(rotation, 0.0, 1.0, 0.0);
        glCallList(animatedDisplayListId);

        rotation += 1.0f;
    }
};

using namespace GLEditor;
using namespace GLEditor::Internal;

namespace GLEditor {
namespace Internal {

class GLViewportPrivate : protected QGLFunctions
{
public:
    GLViewport *q;
    GLWidget *widget;
    GLWidgetSplit *split;
    QColor backgroundColor;
    QGLFramebufferObject *staticFBO;
    QGLFramebufferObject *animatedFBO;
    QList<GLuint> textureIds;
    Testing testing;

    GLViewportPrivate(GLViewport *q, GLWidgetSplit *split)
        :   q(q)
        ,   widget(split->widget())
        ,   split(split)
        ,   backgroundColor(QColor(251, 251, 251, 127))
        ,   staticFBO(0)
        ,   animatedFBO(0)
    {
        initializeGLFunctions(widget->context());
        initFBOs(split->width(), split->height());
        testing.initDisplayLists();
        updateStaticFBO();
        updateAnimatedFBO();
    }

    ~GLViewportPrivate()
    {
        delete animatedFBO;  animatedFBO = 0;
        delete staticFBO;  staticFBO = 0;
        split = 0;
        widget = 0;
        q = 0;
    }

    void initFBOs(int w, int h)
    {
        if (w < 1)
            w = 1;
        if (h < 1)
            h = 1;

        delete staticFBO;
        staticFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(staticFBO);
        Q_ASSERT(staticFBO->isValid());

        delete animatedFBO;
        animatedFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(animatedFBO);
        Q_ASSERT(animatedFBO->isValid());

        textureIds.clear();
        textureIds.append(staticFBO->texture());
        textureIds.append(animatedFBO->texture());
    }

    void updateStaticFBO()
    {
        const QSize size = staticFBO->size();
        const int w = size.width();
        const int h = size.height();
        const GLfloat aspect = w / GLfloat(h ? h : 1);

        Q_CHECK(staticFBO->bind());
        qglPushState();

        widget->qglClearColor(backgroundColor);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_FLAT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0, 0, w, h);

        testing.drawStaticFBO(aspect);

        qglPopState();
        Q_CHECK(staticFBO->release());
        Q_CHECK_GLERROR;
    }

    void updateAnimatedFBO()
    {
        const QSize size = animatedFBO->size();
        const int w = size.width();
        const int h = size.height();
        const GLfloat aspect = w / GLfloat(h ? h : 1);

        Q_CHECK(animatedFBO->bind());
        qglPushState();

        widget->qglClearColor(backgroundColor);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glShadeModel(GL_FLAT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0, 0, w, h);

        testing.drawAnimatedFBO(aspect);

        qglPopState();
        Q_CHECK(animatedFBO->release());
        Q_CHECK_GLERROR;
    }

    void resizeFBOs(int w, int h)
    {
        QGLFramebufferObject *oldFBO = staticFBO;
        QGLFramebufferObject *newFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(newFBO);
        Q_ASSERT(newFBO->isValid());

        staticFBO = newFBO;
        updateStaticFBO();
        textureIds[0] = staticFBO->texture();
        delete oldFBO;

        oldFBO = animatedFBO;
        newFBO = new QGLFramebufferObject(w, h);
        Q_CHECK_PTR(newFBO);
        Q_ASSERT(newFBO->isValid());

        animatedFBO = newFBO;
        updateAnimatedFBO();
        textureIds[1] = animatedFBO->texture();
        delete oldFBO;
    }
};

} // namespace Internal
} // namespace Editor3D

GLViewport::GLViewport(GLWidgetSplit *split)
    :   d(new GLViewportPrivate(this, split))
{
    Q_CHECK_PTR(d);
}

GLViewport::~GLViewport()
{
    delete d;  d = 0;
}

void GLViewport::setBackgroundColor(const QColor &color)
{
    if (d->backgroundColor == color)
        return;

    d->backgroundColor = color;
    d->backgroundColor.setAlphaF(0.5);

    d->updateStaticFBO();
    d->updateAnimatedFBO();
}

QPoint GLViewport::pos() const
{
    return d->split->pos();
}

QRect GLViewport::rect() const
{
    return d->split->rect();
}

QSize GLViewport::size() const
{
    return d->split->size();
}

void GLViewport::resize(int w, int h)
{
    d->resizeFBOs(w, h);
}

void GLViewport::updateAnimation()
{
    d->updateAnimatedFBO();
}

const QList<GLuint> &GLViewport::textureIds() const
{
    return d->textureIds;
}

void GLViewport::draw()
{
    d->widget->drawViewport(this);
}
