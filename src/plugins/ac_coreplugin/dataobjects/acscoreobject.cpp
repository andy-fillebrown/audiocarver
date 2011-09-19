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

#include "acscoreobject.h"

#include <accontrolcurve.h>
#include <acpitchcurve.h>

#include <QGraphicsItem>

static void setParentGraphicsItems(const QMap<Ac::SceneType, QGraphicsItem*> &items,
                                   const QMap<Ac::SceneType, QGraphicsItem*> &parentItems)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        Ac::SceneType type = Ac::SceneType(i);
        QGraphicsItem *parentItem = parentItems.value(type, 0);
        QGraphicsItem *item = items.value(type, 0);
        if (item && parentItem)
            item->setParentItem(parentItem);
    }
}

static void clearParentGraphicsItems(const QMap<Ac::SceneType, QGraphicsItem*> &items)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *item = items.value(Ac::SceneType(i), 0);
        if (item)
            item->setParentItem(0);
    }
}

ScoreObjectPrivate::ScoreObjectPrivate(ScoreObject *q)
    :   ObjectPrivate(q)
    ,   volume(1.0f)
    ,   pitchCurve(0)
    ,   controlCurves(0)
{}

void ScoreObjectPrivate::init()
{
    pitchCurve = new PitchCurve(q_ptr);
    controlCurves = new ObjectList<ControlCurve>(q_ptr);
    updateGraphicsParent();
}

ScoreObjectPrivate::~ScoreObjectPrivate()
{
    delete pitchCurve;
    qDeleteAll(controlCurves);
    qDeleteAll(unitYGraphicsItems);
    qDeleteAll(unitXGraphicsItems);
    qDeleteAll(mainGraphicsItems);
}

void ScoreObjectPrivate::updateGraphicsParent()
{
    Q_Q(ScoreObject);
    ScoreObject *graphicsParent = q->graphicsParent();
    if (graphicsParent) {
        ScoreObjectPrivate *graphicsParent_d = graphicsParent->d_func();
        setParentGraphicsItems(mainGraphicsItems, graphicsParent_d->mainGraphicsItems);
        setParentGraphicsItems(unitXGraphicsItems, graphicsParent_d->unitXGraphicsItems);
        setParentGraphicsItems(unitYGraphicsItems, graphicsParent_d->unitYGraphicsItems);
    } else {
        clearParentGraphicsItems(mainGraphicsItems);
        clearParentGraphicsItems(unitXGraphicsItems);
        clearParentGraphicsItems(unitYGraphicsItems);
    }
}

ScoreObject::ScoreObject(ScoreObjectPrivate &dd, QObject *parent)
    :   Object(dd, parent)
{}

qreal ScoreObject::volume() const
{
    Q_D(const ScoreObject);
    return d->volume;
}

void ScoreObject::setVolume(qreal volume)
{
    Q_D(ScoreObject);
    if (d->volume == volume)
        return;
    d->beginChangeData();
    d->volume = volume;
    d->endChangeData();
}

void ScoreObject::setParent(Object *parent)
{
    Q_D(ScoreObject);
    Object::setParent(parent);
    d->updateGraphicsParent();
}

PitchCurve *ScoreObject::pitchCurve() const
{
    Q_D(const ScoreObject);
    return d->pitchCurve;
}

ObjectList<ControlCurve> *ScoreObject::controlCurves() const
{
    Q_D(const ScoreObject);
    return d->controlCurves;
}

QVariant ScoreObject::data(int role) const
{
    switch (role) {
    case Ac::LengthRole:
        return length();
    case Ac::VolumeRole:
        return volume();
    default:
        return Object::data(role);
    }
}

bool ScoreObject::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::VolumeRole:
        setVolume(value.toReal());
        return true;
    default:
        return Object::setData(value, role);
    }
}

int ScoreObject::modelItemIndex(IModelItem *item) const
{
    Q_D(const ScoreObject);
    if (d->pitchCurve == item)
        return 0;
    if (d->controlCurves == item)
        return 1;
    return Object::modelItemIndex(item);
}

IModelItem *ScoreObject::modelItemAt(int i) const
{
    switch (i) {
    case 0:
        return pitchCurve();
    case 1:
        return controlCurves();
    default:
        return 0;
    }
}

IModelItem *ScoreObject::findModelItem(Ac::ItemType type) const
{
    switch (type) {
    case Ac::PitchCurveItem:
        return pitchCurve();
    default:
        return 0;
    }
}

IModelItem *ScoreObject::findModelItemList(Ac::ItemType type) const
{
    switch (type) {
    case Ac::ControlCurveItem:
        return controlCurves();
    default:
        return 0;
    }
}
