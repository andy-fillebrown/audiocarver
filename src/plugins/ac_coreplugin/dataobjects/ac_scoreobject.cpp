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

#include "ac_scoreobject.h"

#include <ac_controlcurve.h>
#include <ac_pitchcurve.h>

#include <QGraphicsItem>

ScoreObjectPrivate::ScoreObjectPrivate(ScoreObject *q)
    :   GraphicsParentPrivate(q)
    ,   volume(1.0f)
    ,   pitchCurve(0)
    ,   controlCurves(0)
    ,   dragging(quint32(false))
{}

void ScoreObjectPrivate::init()
{
    pitchCurve = new PitchCurve(q_ptr);
    controlCurves = new ObjectTList<ControlCurve>(q_ptr);
}

ScoreObjectPrivate::~ScoreObjectPrivate()
{
    qDeleteAll(controlCurves);
    delete pitchCurve;
    delete controlCurves;
}

ScoreObject::ScoreObject(ScoreObjectPrivate &dd, QObject *parent)
    :   GraphicsParent(dd, parent)
{
    dd.init();
}

qreal ScoreObject::volume() const
{
    Q_D(const ScoreObject);
    return d->volume;
}

void ScoreObject::setVolume(qreal volume, Ac::DragState dragState)
{
    Q_D(ScoreObject);
    volume = qBound(qreal(0.0f), volume, qreal(1.0f));
    if (d->volume == volume) {
        if (Ac::NotDragging == dragState && d->dragging) {
            d->endChangeData();
            d->dragging = false;
        }
        return;
    }
    if (Ac::NotDragging == dragState || !d->dragging)
        d->beginChangeData();
    if (Ac::Dragging == dragState)
        d->dragging = true;
    d->volume = volume;
    updatePoints();
    if (!d->dragging)
        d->endChangeData();
    if (Ac::NotDragging == dragState)
        d->dragging = false;
}

PitchCurve *ScoreObject::pitchCurve() const
{
    Q_D(const ScoreObject);
    return d->pitchCurve;
}

ObjectTList<ControlCurve> *ScoreObject::controlCurves() const
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

int ScoreObject::modelItemIndex(const IModelItem *item) const
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

IModelItem *ScoreObject::findModelItem(int type) const
{
    switch (type) {
    case Ac::PitchCurveItem:
        return pitchCurve();
    default:
        return 0;
    }
}

IModelItem *ScoreObject::findModelItemList(int type) const
{
    switch (type) {
    case Ac::ControlCurveItem:
        return controlCurves();
    default:
        return 0;
    }
}
