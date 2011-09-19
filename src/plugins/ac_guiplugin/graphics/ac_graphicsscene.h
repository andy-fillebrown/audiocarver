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

#include <accoreenums.h>
#include <acmodel.h>

#include <QGraphicsScene>

#include <QAbstractItemModel>

class HScene : public QGraphicsScene
{
public:
    HScene(QObject *parent = 0)
        :   QGraphicsScene(parent)
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
        return 10.0f;
    }
};

class PitchLabelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PitchLabelScene(QObject *parent = 0)
        :   QGraphicsScene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 127.0f);
    }
};

class ControlLabelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ControlLabelScene(QObject *parent = 0)
        :   QGraphicsScene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 1.0f);
    }
};

class SceneManager : public QObject
{
    Q_OBJECT

public:
    SceneManager(QObject *parent = 0)
        :   QObject(parent)
        ,   _model(0)
        ,   _pitchScene(new PitchScene(this))
        ,   _controlScene(new ControlScene(this))
        ,   _timeLabelScene(new TimeLabelScene(this))
        ,   _pitchLabelScene(new PitchLabelScene(this))
        ,   _controlLabelScene(new ControlLabelScene(this))
    {}

    ~SceneManager()
    {
        delete _model;
    }

    QAbstractItemModel *model() const { return _model; }
    void setModel(Model *model)
    {
        if (_model == model)
            return;
        _model = model;
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            Ac::SceneType type = Ac::SceneType(i);
            scene(type)->addItem(_model->sceneItem(type));
        }
    }

    QGraphicsScene *scene(Ac::SceneType type)
    {
        switch (type) {
        case Ac::PitchScene:
            return _pitchScene;
        case Ac::ControlScene:
            return _controlScene;
        case Ac::TimeLabelScene:
            return _timeLabelScene;
        case Ac::PitchLabelScene:
            return _pitchLabelScene;
        case Ac::ControlLabelScene:
            return _controlLabelScene;
        default:
            return 0;
        }
    }

private:
    Model *_model;
    PitchScene *_pitchScene;
    ControlScene *_controlScene;
    TimeLabelScene *_timeLabelScene;
    PitchLabelScene *_pitchLabelScene;
    ControlLabelScene *_controlLabelScene;
};

#endif // AC_GRAPHICSSCENE_H
