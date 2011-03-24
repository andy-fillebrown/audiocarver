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

#include "scene.h"

#include "classes/scorenode.h"

#include <glutils/glutils_global.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class SceneImplPrivate
{
public:
    SceneImpl *q;
    ScoreNode *scoreNode;
    GLuint staticDisplayListId;
    GLuint animationDisplayListId;
    float rotation;

    SceneImplPrivate(SceneImpl *q)
        :   q(q)
        ,   scoreNode(0) // allocated in init()
        ,   staticDisplayListId(-1)
        ,   animationDisplayListId(-1)
        ,   rotation(0.0f)
    {
    }

    ~SceneImplPrivate()
    {
        rotation = 0.0f;
        animationDisplayListId = 0;
        staticDisplayListId  = 0;
        scoreNode = 0;
        q = 0;
    }

    /// Assumes GL context is active.
    void init()
    {
        scoreNode = new ScoreNode(q);
        Q_CHECK_PTR(scoreNode);

        staticDisplayListId = glGenLists(1);
        glNewList(staticDisplayListId, GL_COMPILE);
        drawStaticGeometry();
        glEndList();
        Q_CHECK_GLERROR;

        animationDisplayListId = glGenLists(1);
        glNewList(animationDisplayListId, GL_COMPILE);
        drawAnimationGeometry();
        glEndList();
        Q_CHECK_GLERROR;
    }

    /// Assumes GL context is active.
    void destroy()
    {
        glDeleteLists(animationDisplayListId, 1);  animationDisplayListId = -1;
        glDeleteLists(staticDisplayListId, 1);  staticDisplayListId = -1;
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

    void drawAnimationGeometry()
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

    void drawStaticFBO()
    {
        glCallList(staticDisplayListId);
    }

    void drawAnimationFBO()
    {
        glRotatef(rotation, 0.0, 1.0, 0.0);
        glCallList(animationDisplayListId);
    }
};

} // namespace Internal
} // namespace AudioCarver

SceneImpl::SceneImpl()
    :   d(new SceneImplPrivate(this))
{
}

SceneImpl::~SceneImpl()
{

    delete d;  d = 0;
}

void SceneImpl::initialize()
{
    d->init();
}

void SceneImpl::destroy()
{
    d->destroy();
}

bool SceneImpl::drawBackground()
{
    return false;
}

bool SceneImpl::drawStatic()
{
    d->drawStaticFBO();
    return true;
}

bool SceneImpl::drawModel()
{
    return false;
}

bool SceneImpl::drawEdit()
{
    return false;
}

bool SceneImpl::drawAnimation(qreal time)
{
    d->rotation = 90.0 * time;
    d->drawAnimationFBO();
    return true;
}

bool SceneImpl::drawOverlay()
{
    return false;
}
