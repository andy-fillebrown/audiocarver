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

ScoreObjectPrivate::ScoreObjectPrivate(ScoreObject *q)
    :   ObjectPrivate(q)
    ,   volume(1.0f)
    ,   pitchCurve(0)
    ,   controlCurves(0)
{}

void ScoreObjectPrivate::init()
{
    pitchCurve = new PitchCurve(q);
    controlCurves = new ObjectList<ControlCurve>(q);
}

ScoreObject::ScoreObject(ScoreObjectPrivate &dd, QObject *parent)
    :   Object(dd, parent)
{
    Q_D(ScoreObject);
    d->init();
}

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
    d->volume = volume;
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
    case LengthRole:
        return length();
    case VolumeRole:
        return volume();
    default:
        return Object::data(role);
    }
}

bool ScoreObject::setData(const QVariant &value, int role)
{
    switch (role) {
    case VolumeRole:
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

IModelItem *ScoreObject::findModelItem(ItemType type) const
{
    switch (type) {
    case PitchCurveItem:
        return pitchCurve();
    default:
        return 0;
    }
}

IModelItem *ScoreObject::findModelItemList(ItemType type) const
{
    switch (type) {
    case ControlCurveItem:
        return controlCurves();
    default:
        return 0;
    }
}
