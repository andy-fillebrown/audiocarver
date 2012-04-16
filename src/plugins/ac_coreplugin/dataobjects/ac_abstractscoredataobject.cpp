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

#include "ac_abstractscoredataobject.h"

#include <ac_controlcurvedataobject.h>
#include <ac_pitchcurvedataobject.h>

#include <mi_idataobjectfactory.h>
#include <mi_scopeddatachange.h>

Q_IAGGREGATOR_INIT_ROLES(AbstractScoreDataObject) =
{
Ac::VolumeRole
};

Q_IAGGREGATOR_INIT_ITEMTYPES(AbstractScoreDataObject) =
{
Ac::PitchCurveItem,
Mi::ListItem
};

IAggregator *AbstractScoreDataObject::init()
{
    IDataObjectFactory *factory = IDataObjectFactory::instance();
    _pitchCurve = factory->createObject(Ac::PitchCurveItem);
    _controlCurves = factory->createObjectList(Ac::ControlCurveItem);
    Q_IAGGREGATOR_INIT_ITEMLIST__INITIALIZER = {
        _pitchCurve,
        _controlCurves,
    };
    Q_IAGGREGATOR_INIT_ITEMLIST
    return Base::init();
}

AbstractScoreDataObject::~AbstractScoreDataObject()
{
    delete _controlCurves;
    delete _pitchCurve;
}

IAggregate *AbstractScoreDataObject::ModelData::init()
{
    return Base::init();
}

IAggregate *AbstractScoreDataObject::ModelItem::init()
{
    return Base::init();
}

bool AbstractScoreDataObject::setVolume(qreal volume)
{
    volume = qBound(qreal(0.0f), volume, qreal(1.0f));
    if (_volume == volume)
        return false;
    Q_SCOPED_DATA_CHANGE((Ac::VolumeRole));
    _volume = volume;
    updatePoints();
    return true;
}
