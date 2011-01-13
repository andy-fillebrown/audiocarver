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

#include "viewport3d.h"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include <QtOpenGL/QGLFramebufferObject>

using namespace Editor3D;

Viewport3D::Viewport3D(QWidget *parent)
    :   QGLWidget(parent)
    ,   _fbo(0)
{
}

Viewport3D::~Viewport3D()
{
    _fbo = 0;
}

void Viewport3D::initializeGL()
{
    _fbo = new QGLFramebufferObject(512, 512);

    bool ok = _fbo->bind();
    Q_ASSERT(ok);

    draw();

    ok = _fbo->release();
    Q_ASSERT(ok);
}

void Viewport3D::paintGL()
{
    saveGLState();

    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 1, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, 0, width(), height());

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _fbo->texture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);  glVertex2i(0, 0);
    glTexCoord2i(1, 1);  glVertex2i(1, 0);
    glTexCoord2i(1, 0);  glVertex2i(1, 1);
    glTexCoord2i(0, 0);  glVertex2i(0, 1);
    glEnd();

    restoreGLState();
}

void Viewport3D::draw()
{
    static const GLfloat rotationX = 0;
    static const GLfloat rotationY = 45;
    static const GLfloat rotationZ = 0;

    static const GLfloat P1[3] = { 0.0, -1.0, +2.0 };
    static const GLfloat P2[3] = { +1.73205081, -1.0, -1.0 };
    static const GLfloat P3[3] = { -1.73205081, -1.0, -1.0 };
    static const GLfloat P4[3] = { 0.0, +2.0, 0.0 };

    static const GLfloat * const coords[4][3] = {
        { P1, P2, P3 }, { P1, P3, P4 }, { P1, P4, P2 }, { P2, P4, P3 }
    };
    static const QColor faceColors[] = {
        Qt::red, Qt::green, Qt::blue, Qt::yellow
    };

    saveGLState();

    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat x = GLfloat(512) / 512;
    glViewport(0, 0, 512, 512);
    glFrustum(-x, +x, -1.0, +1.0, 4.0, 15.0);

    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    for (int i = 0; i < 4; ++i) {
        glLoadName(i);
        glBegin(GL_TRIANGLES);
        qglColor(faceColors[i]);
        for (int j = 0; j < 3; ++j)
            glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
        glEnd();
    }

    restoreGLState();
}

void Viewport3D::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void Viewport3D::restoreGLState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}
