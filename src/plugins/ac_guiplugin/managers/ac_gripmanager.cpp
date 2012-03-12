/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_gripmanager.h"

#include <ac_igripitem.h>

#include <ac_namespace.h>

class GripManagerPrivate
{
public:
    GripManager *q;
    QList<IGripItem*> pitchGrips;
    QList<IGripItem*> controlGrips;

    GripManagerPrivate(GripManager *q)
        :   q(q)
    {}

    void appendPitchGrip(IGripItem *grip)
    {
        if (pitchGrips.contains(grip))
            return;
        pitchGrips.append(grip);
        qSort(pitchGrips.begin(), pitchGrips.end(), IGripItem::lessThan);
    }

    void appendControlGrip(IGripItem *grip)
    {
        if (controlGrips.contains(grip))
            return;
        controlGrips.append(grip);
        qSort(controlGrips.begin(), controlGrips.end(), IGripItem::lessThan);
    }
};

static GripManager *instance = 0;

GripManager::GripManager(QObject *parent)
    :   QObject(parent)
    ,   d(new GripManagerPrivate(this))
{
    ::instance = this;
}

GripManager::~GripManager()
{
    delete d;
}

GripManager *GripManager::instance()
{
    return ::instance;
}

int GripManager::gripCount(int sceneType) const
{
    switch (sceneType) {
    case Ac::PitchScene:
        return d->pitchGrips.count();
    case Ac::ControlScene:
        return d->controlGrips.count();
    default:
        return -1;
    }
}

IGripItem *GripManager::gripAt(int sceneType, int i) const
{
    switch (sceneType) {
    case Ac::PitchScene:
        return d->pitchGrips.at(i);
    case Ac::ControlScene:
        d->controlGrips.at(i);
    default:
        return 0;
    }
}

void GripManager::appendGrip(int sceneType, IGripItem *grip)
{
    switch (sceneType) {
    case Ac::PitchScene:
        d->appendPitchGrip(grip);
        break;
    case Ac::ControlScene:
        d->appendControlGrip(grip);
        break;
    default:
        break;
    }
}

void GripManager::removeGrip(int sceneType, IGripItem *grip)
{
    switch (sceneType) {
    case Ac::PitchScene:
        d->pitchGrips.removeOne(grip);
        break;
    case Ac::ControlScene:
        d->controlGrips.removeOne(grip);
        break;
    default:
        break;
    }
}
