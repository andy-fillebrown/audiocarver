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

#include "ac_score.h"

#include <ac_graphicsitem.h>
#include <ac_gridsettings.h>
#include <ac_track.h>
#include <ac_viewsettings.h>

ScorePrivate::ScorePrivate(Score *q)
    :   ScoreObjectPrivate(q)
    ,   length(128.0f)
    ,   tracks(0)
    ,   viewSettings(0)
    ,   gridSettings(0)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
        mainGraphicsItems.insert(Ac::SceneType(i), new GraphicsRootItem);
    unitXGraphicsItems.insert(Ac::PitchScene, new GraphicsItem(mainGraphicsItems[Ac::PitchScene]));
    unitXGraphicsItems.insert(Ac::ControlScene, new GraphicsItem(mainGraphicsItems[Ac::ControlScene]));
    unitYGraphicsItems.insert(Ac::PitchScene, new GraphicsItem(mainGraphicsItems[Ac::PitchScene]));
    unitXGraphicsItems[Ac::PitchScene]->setTransform(QTransform::fromScale(length, 1.0f));
    unitXGraphicsItems[Ac::ControlScene]->setTransform(QTransform::fromScale(length, 1.0f));
    unitYGraphicsItems[Ac::PitchScene]->setTransform(QTransform::fromScale(1.0f, 127.0f));
}

void ScorePrivate::init()
{
    tracks = new ObjectList<Track>(q_ptr);
    viewSettings = new ViewSettings(q_ptr);
    gridSettings = new GridSettings(q_ptr);
}

ScorePrivate::~ScorePrivate()
{
    delete gridSettings;
    delete viewSettings;
    qDeleteAll(tracks);
    delete tracks;
}

void ScorePrivate::updateLength()
{
//    foreach (QGraphicsItem *item, unitXGraphicsItems)
//        item->setTransform(QTransform::fromScale(length, 1.0f));
}

Score::Score(QObject *parent)
    :   ScoreObject(*(new ScorePrivate(this)), parent)
{
    Q_D(Score);
    d->init();
    setObjectName("Score");
}

qreal Score::length() const
{
    Q_D(const Score);
    return d->length;
}

void Score::setLength(qreal length)
{
    Q_D(Score);
    if (d->length == length)
        return;
    d->beginChangeData();
    d->length = length;
    d->updateLength();
    d->endChangeData();
}

ObjectList<Track> *Score::tracks() const
{
    Q_D(const Score);
    return d->tracks;
}

ViewSettings *Score::viewSettings() const
{
    Q_D(const Score);
    return d->viewSettings;
}

GridSettings *Score::gridSettings() const
{
    Q_D(const Score);
    return d->gridSettings;
}

QGraphicsItem *Score::sceneItem(Ac::SceneType type) const
{
    Q_D(const Score);
    return d->mainGraphicsItems[type];
}

void Score::setModel(Model *model)
{
    d_ptr->setModel(model);
}

int Score::modelItemIndex(IModelItem *item) const
{
    Q_D(const Score);
    if (d->tracks == item)
        return ScoreObject::ModelItemCount;
    if (d->viewSettings == item)
        return ScoreObject::ModelItemCount + 1;
    if (d->gridSettings == item)
        return ScoreObject::ModelItemCount + 2;
    return ScoreObject::modelItemIndex(item);
}

IModelItem *Score::modelItemAt(int i) const
{
    switch (i) {
    case ScoreObject::ModelItemCount:
        return tracks();
    case ScoreObject::ModelItemCount + 1:
        return viewSettings();
    case ScoreObject::ModelItemCount + 2:
        return gridSettings();
    default:
        return ScoreObject::modelItemAt(i);
    }
}

IModelItem *Score::findModelItemList(Ac::ItemType type) const
{
    switch (type) {
    case Ac::TrackItem:
        return tracks();
    default:
        return ScoreObject::findModelItemList(type);
    }
}

bool Score::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::LengthRole:
        setLength(value.toReal());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}
