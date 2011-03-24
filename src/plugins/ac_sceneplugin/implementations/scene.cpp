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

using namespace GL;

namespace AudioCarver {
namespace Internal {

class SceneImplPrivate
{
public:
    SceneImpl *q;
    ScoreNode *scoreNode;
    GLuint staticDisplayListId;
    GLuint animationDisplayListId;
    real rotation;

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
        static const real x = 1.0f;
        static const real y = 1.0f;
        static const real S1[3] = { x, y, 0.0f };
        static const real S2[3] = { x, -y, 0.0f };
        static const real S3[3] = { -x, -y, 0.0f };
        static const real S4[3] = { -x, y, 0.0f };
        static const real * const coordsS[2][3] = {
            { S1, S2, S3 }, { S1, S3, S4 }
        };
        glBegin(GL_TRIANGLES);
        glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
        for (int i = 0;  i < 2;  ++i) {
            for (int j = 0;  j < 3;  ++j)
                glVertex3f(coordsS[i][j][0], coordsS[i][j][1], coordsS[i][j][2]);
        }
        glEnd();

        Q_CHECK_GLERROR;
    }

    void drawAnimationGeometry()
    {
        static const real A1[3] = { 0.0f, -1.0f, 2.0f };
        static const real A2[3] = { -1.73205081f, -1.0f, -1.0f };
        static const real A3[3] = { 1.73205081f, -1.0f, -1.0f };
        static const real A4[3] = { 0.0f, 2.0f, 0.0f };
        static const real * const coordsA[4][3] = {
            { A1, A2, A3 }, { A1, A3, A4 }, { A1, A4, A2 }, { A2, A4, A3 }
        };
        static const real faceColorsA[][3] = {
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }
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
        glRotatef(rotation, 0.0f, 1.0f, 0.0f);
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
    glTranslatef(0.0f, 0.0f, 10.0f);
    return drawStatic();
//    return false;
}

bool SceneImpl::drawEdit()
{
    glTranslatef(0.0f, 0.0f, 20.0f);
    return drawStatic();
//    return false;
}

bool SceneImpl::drawAnimation(qreal time)
{
    d->rotation = 90.0 * time;
    d->drawAnimationFBO();
    return true;
}

bool SceneImpl::drawOverlay()
{
    glTranslatef(0.0f, 0.0f, 20.0f);
    return drawAnimation(d->rotation / 90.0);
//    return false;
}
