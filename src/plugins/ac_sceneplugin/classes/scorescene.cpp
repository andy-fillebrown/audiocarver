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

template <typename T> class GLBuffer;

template <typename T>
class GLSubArray
{
public:
    GLBuffer<T> *buffer;
    int start;
    int count;

    int end() const
    {
        return start + count;
    }

    void write(T *data);
};

template <typename T>
class GLBuffer
{
public:
    QGLBuffer buffer;
    int count;
    QList<GLSubArray<T> > subArrays;

    GLBuffer(QGLBuffer::Type type, int count)
        :   buffer(type)
        ,   count(count)
    {
        bool ok = buffer.create();
        Q_ASSERT(ok);
        buffer.setUsagePattern(QGLBuffer::DynamicDraw);
        buffer.allocate(count * sizeof(T));
    }

    ~GLBuffer()
    {
    }

    int createSubArray(int count)
    {
        GLSubArray<T> subArray;
        subArray.buffer = this;
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

template <typename T>
void GLSubArray<T>::write(T *data)
{
    bool ok = buffer->buffer.bind();
    Q_ASSERT(ok);

    buffer->buffer.write(start, data, count);

    buffer->buffer.release();
}

class GLNoteSubArray
{
public:
    int vboId;
    int pointCount;
    FCurveScene *pitchCurve;
    FCurveScene *volumeCurve;
};

class ScoreScenePrivate
{
public:
    ScoreScene *q;
    Score *score;
    QList<FCurveScene*> curves;
    QList<TrackScene*> tracks;
    GLBuffer<float> vbo;
    GLBuffer<quint32> ibo;
    QList<GLNoteSubArray> noteSubArrays;
    QList<NoteScene*> notes;

    ScoreScenePrivate(ScoreScene *q)
        :   q(q)
        ,   score(Score::instance())
        ,   vbo(QGLBuffer::VertexBuffer, 2048000) // 8 MB?
        ,   ibo(QGLBuffer::IndexBuffer, 2048000) // 8 MB?
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

int ScoreScene::createVBOSubArray(int count)
{
    return d->vbo.createSubArray(count);
}

int ScoreScene::createVBOSubArray(NoteScene *note)
{
    Q_ASSERT(false && "Not implemented yet");
    return -1;
}

void ScoreScene::setVBOSubArray(int i, float *data)
{
    d->vbo.subArrays[i].write(data);
}

void ScoreScene::removeVBOSubArray(int i)
{
    d->vbo.subArrays.removeAt(i);
}

void ScoreScene::bindVBO()
{
    bool ok = d->vbo.buffer.bind();
    Q_ASSERT(ok);
}

void ScoreScene::releaseVBO()
{
    d->vbo.buffer.release();
}

int ScoreScene::createIBOSubArray(int count)
{
    return d->ibo.createSubArray(count);
}

void ScoreScene::setIBOSubArray(int i, quint32 *data)
{
    d->ibo.subArrays[i].write(data);
}

void ScoreScene::removeIBOSubArray(int i)
{
    d->ibo.subArrays.removeAt(i);
}

void ScoreScene::bindIBO()
{
    bool ok = d->ibo.buffer.bind();
    Q_ASSERT(ok);
}

void ScoreScene::releaseIBO()
{
    d->ibo.buffer.release();
}

void ScoreScene::appendNote(NoteScene *note)
{
    if (!d->notes.contains(note))
        d->notes.append(note);
}

void ScoreScene::removeNote(NoteScene *note)
{
    d->notes.removeOne(note);
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
