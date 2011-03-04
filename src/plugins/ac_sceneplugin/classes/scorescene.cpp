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

#include "scorescene.h"

#include <classes/fcurvescene.h>
#include <classes/trackscene.h>

#include <ac_databaseplugin/classes/score.h>

#include <databaseplugin/classes/list.h>

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLBuffer>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class GLVertexBufferObject;

class GLVertexBufferSubArray
{
public:
    GLVertexBufferObject *vbo;
    int start;
    int count;

    int end() const
    {
        return start + count;
    }

    void write(float *data);
};

class GLVertexBufferObject : protected QGLFunctions
{
public:
    QGLBuffer buffer;
    int count;
    QList<GLVertexBufferSubArray> subArrays;

    GLVertexBufferObject(int count)
        :   buffer(QGLBuffer::VertexBuffer)
        ,   count(count)
    {
        initializeGLFunctions();

        bool ok = buffer.create();
        Q_ASSERT(ok);
        buffer.setUsagePattern(QGLBuffer::DynamicDraw);
        buffer.allocate(count * sizeof(float));
    }

    ~GLVertexBufferObject()
    {
    }

    int createSubArray(int count)
    {
        GLVertexBufferSubArray subArray;
        subArray.vbo = this;
        subArray.count = count;

        int start = 0;

        if (!subArrays.isEmpty()) {
            // Search for unused area between sub-arrays large enough for count.
            start = subArrays.first().end();

            for (int i = 1;  i < subArrays.count();  ++i) {
                if (count <= subArrays.at(i).start - start) {
                    subArray.start = start;
                    subArrays.insert(i, subArray);

                    return i;
                }
            }

            // No unused area found between sub-arrays.
            start = subArrays.last().end();
        }

        subArray.start = start;
        subArrays.append(subArray);

        return subArrays.count() - 1;
    }
};

void GLVertexBufferSubArray::write(float *data)
{
    bool ok = vbo->buffer.bind();
    Q_ASSERT(ok);

    vbo->buffer.write(start, data, count);

    vbo->buffer.release();
}

class ScoreScenePrivate
{
public:
    ScoreScene *q;
    Score *score;
    QList<FCurveScene*> curves;
    QList<TrackScene*> tracks;

    ScoreScenePrivate(ScoreScene *q)
        :   q(q)
        ,   score(Score::instance())
    {
    }

    ~ScoreScenePrivate()
    {
    }

    void updateCurves()
    {
        ac_updateSceneList_helper(curves, score->curves()->data(), q);
    }

    void updateTracks()
    {
        ac_updateSceneList_helper(tracks, score->tracks()->data(), q);
    }
};

} // Internal
} // AudioCarver

ScoreScene::ScoreScene(QObject *parent)
    :   SceneObject(Score::instance(), parent)
    ,   d(new Internal::ScoreScenePrivate(this))
{
}

ScoreScene::~ScoreScene()
{
}

void ScoreScene::updateProperty(int index)
{
    const QString propertyName = d->score->propertyName(index);

    if (propertyName == "curves") {
        d->updateCurves();
        return;
    }

    if (propertyName == "tracks") {
        d->updateTracks();
        return;
    }

    SceneObject::updateProperty(index);
}
