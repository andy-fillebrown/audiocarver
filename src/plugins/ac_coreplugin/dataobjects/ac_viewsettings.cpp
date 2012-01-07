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

#include "ac_viewsettings.h"

#include <ac_score.h>

#include <QVariant>

ViewSettings::ViewSettings(QObject *parent)
    :   Object(*(new ViewSettingsPrivate(this)), parent)
{
    setName("View Settings");
}

qreal ViewSettings::timePosition() const
{
    Q_D(const ViewSettings);
    return d->timePos;
}

void ViewSettings::setTimePosition(qreal pos)
{
    Q_D(ViewSettings);
    pos = qBound(qreal(0.0f), pos, score()->length());
    if (d->timePos == pos)
        return;
    d->beginChangeData();
    d->timePos = pos;
    d->endChangeData();
}

qreal ViewSettings::pitchPosition() const
{
    Q_D(const ViewSettings);
    return d->pitchPos;
}

void ViewSettings::setPitchPosition(qreal pos)
{
    Q_D(ViewSettings);
    pos = qBound(qreal(0.0f), pos, qreal(127.0f));
    if (d->pitchPos == pos)
        return;
    d->beginChangeData();
    d->pitchPos = pos;
    d->endChangeData();
}

qreal ViewSettings::controlPosition() const
{
    Q_D(const ViewSettings);
    return d->controlPos;
}

void ViewSettings::setControlPosition(qreal pos)
{
    Q_D(ViewSettings);
    pos = qBound(qreal(0.0f), pos, qreal(1.0f));
    if (d->controlPos == pos)
        return;
    d->beginChangeData();
    d->controlPos = pos;
    d->endChangeData();
}

qreal ViewSettings::timeScale() const
{
    Q_D(const ViewSettings);
    return d->timeScale;
}

void ViewSettings::setTimeScale(qreal scale)
{
    Q_D(ViewSettings);
    if (scale < VIEWSCALE_MIN)
        scale = VIEWSCALE_MIN;
    d->beginChangeData();
    d->timeScale = scale;
    d->endChangeData();
}

qreal ViewSettings::pitchScale() const
{
    Q_D(const ViewSettings);
    return d->pitchScale;
}

void ViewSettings::setPitchScale(qreal scale)
{
    Q_D(ViewSettings);
    if (scale < VIEWSCALE_MIN)
        scale = VIEWSCALE_MIN;
    if (d->pitchScale == scale)
        return;
    d->beginChangeData();
    d->pitchScale = scale;
    d->endChangeData();
}

qreal ViewSettings::controlScale() const
{
    Q_D(const ViewSettings);
    return d->controlScale;
}

void ViewSettings::setControlScale(qreal scale)
{
    Q_D(ViewSettings);
    if (scale < VIEWSCALE_MIN)
        scale = VIEWSCALE_MIN;
    if (d->controlScale == scale)
        return;
    d->beginChangeData();
    d->controlScale = scale;
    d->endChangeData();
}

Score *ViewSettings::score() const
{
    return object_cast<Score>(QObject::parent());
}

void ViewSettings::clear()
{
    Q_D(ViewSettings);
    d->clear();
}

QVariant ViewSettings::data(int role) const
{
    switch (role) {
    case Ac::TimePositionRole:
        return timePosition();
    case Ac::PitchPositionRole:
        return pitchPosition();
    case Ac::ControlPositionRole:
        return controlPosition();
    case Ac::TimeScaleRole:
        return timeScale();
    case Ac::PitchScaleRole:
        return pitchScale();
    case Ac::ControlScaleRole:
        return controlScale();
    default:
        return Object::data(role);
    }
}

bool ViewSettings::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::TimePositionRole:
        setTimePosition(value.toReal());
        return true;
    case Ac::PitchPositionRole:
        setPitchPosition(value.toReal());
        return true;
    case Ac::ControlPositionRole:
        setControlPosition(value.toReal());
        return true;
    case Ac::TimeScaleRole:
        setTimeScale(value.toReal());
        return true;
    case Ac::PitchScaleRole:
        setPitchScale(value.toReal());
        return true;
    case Ac::ControlScaleRole:
        setControlScale(value.toReal());
        return true;
    default:
        return Object::setData(value, role);
    }
}
