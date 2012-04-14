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

#include "ac_scoreobject.h"

#include <ac_controlcurve.h>
#include <ac_pitchcurve.h>

#include <mi_idataobjectfactory.h>
#include <mi_scopeddatachange.h>

Q_IAGGREGATOR_INIT_ROLES(ScoreObject) =
{
Ac::VolumeRole
};

Q_IAGGREGATOR_INIT_ITEMTYPES(ScoreObject) =
{
Ac::PitchCurveItem,
Mi::ListItem
};

IAggregator *ScoreObject::init()
{
    IDataObjectFactory *factory = IDataObjectFactory::instance();
    _pitchCurve = factory->createDataObject(Ac::PitchCurveItem);
    _controlCurves = factory->createDataObjectList(Ac::ControlCurveItem);
    Q_IAGGREGATOR_INIT_ITEMLIST_INITIALIZER = {
        _pitchCurve,
        _controlCurves,
    };
    Q_IAGGREGATOR_INIT_ITEMLIST
    return Base::init();
}

ScoreObject::~ScoreObject()
{
    delete _controlCurves;
    delete _pitchCurve;
}

IAggregate *ScoreObject::ModelData::init()
{
    return Base::init();
}

IAggregate *ScoreObject::ModelItem::init()
{
    return Base::init();
}

bool ScoreObject::setVolume(qreal volume)
{
    volume = qMin(qMax(qreal(0.0f), volume), qreal(1.0f));
    if (_volume == volume)
        return false;
    Q_SCOPED_DATA_CHANGE((Ac::VolumeRole));
    _volume = volume;
    updatePoints();
    return true;
}
