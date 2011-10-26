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

#ifndef AC_GRAPHICSSCENE_H
#define AC_GRAPHICSSCENE_H

#include <ac_namespace.h>

#include <QGraphicsScene>

class Model;

class QModelIndex;

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(QObject *parent = 0)
        :   QGraphicsScene(parent)
    {
        setItemIndexMethod(NoIndex);
    }
};

class HScene : public Scene
{
    Q_OBJECT

public:
    HScene(QObject *parent = 0)
        :   Scene(parent)
    {}

    void setWidth(qreal w)
    {
        if (w < 0.0f)
            w = 0.0f;
        if (width() == w)
            return;
        setSceneRect(0.0f, 0.0f, w, height());
    }

    virtual qreal height() const = 0;
};

class PitchScene : public HScene
{
    Q_OBJECT

public:
    PitchScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const
    {
        return 127.0f;
    }
};

class ControlScene : public HScene
{
    Q_OBJECT

public:
    ControlScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const
    {
        return 1.0f;
    }
};

class TimeLabelScene : public HScene
{
    Q_OBJECT

public:
    TimeLabelScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const
    {
        return 1.0f;
    }
};

class PitchLabelScene : public Scene
{
    Q_OBJECT

public:
    PitchLabelScene(QObject *parent = 0)
        :   Scene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 127.0f);
    }
};

class ControlLabelScene : public Scene
{
    Q_OBJECT

public:
    ControlLabelScene(QObject *parent = 0)
        :   Scene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 1.0f);
    }
};

class SceneManagerPrivate;
class SceneManager : public QObject
{
    Q_OBJECT

public:
    SceneManager(QObject *parent = 0);
    ~SceneManager();

    static SceneManager *instance();

    Model *model() const;
    void setModel(Model *model);

    QGraphicsScene *scene(int type);

private:
    Q_DISABLE_COPY(SceneManager)
    SceneManagerPrivate *d;
};

#endif // AC_GRAPHICSSCENE_H
