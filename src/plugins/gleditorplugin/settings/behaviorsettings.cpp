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

#include "behaviorsettings.h"

#include <QtCore/QSettings>
#include <QtCore/QString>

static const char * const zoomSpeedKey = "ZoomSpeed";
static const char * const panningZKey = "PanningZ";
static const char * const scrollWheelPanningZKey = "ScrollWheelPanning";
static const char * const scrollWheelZoomingKey = "ScrollWheelZooming";
static const char * const scalingYKey = "ScalingY";
static const char * const rotatingXKey = "RotatingX";
static const char * const linkedViewportModelXformsKey = "LinkedViewportModelXforms";

static const char * const groupPostfix = "BehaviorSettings";

using namespace GLEditor;

BehaviorSettingsData::BehaviorSettingsData()
    :   zoomSpeed(1.0f)
    ,   panningZ(true)
    ,   scrollWheelPanningZ(true)
    ,   scrollWheelZooming(true)
    ,   scalingY(false)
    ,   rotatingX(true)
    ,   linkedViewportModelXforms(true)
{
}

void BehaviorSettings::save(const QString &category, QSettings *s) const
{
    QString group = QLatin1String(groupPostfix);
    if (!category.isEmpty())
        group.insert(0, category);

    s->beginGroup(group);
    s->setValue(QLatin1String(zoomSpeedKey), d.zoomSpeed);
    s->setValue(QLatin1String(panningZKey), d.panningZ);
    s->setValue(QLatin1String(scrollWheelPanningZKey), d.scrollWheelPanningZ);
    s->setValue(QLatin1String(scrollWheelZoomingKey), d.scrollWheelZooming);
    s->setValue(QLatin1String(scalingYKey), d.scalingY);
    s->setValue(QLatin1String(rotatingXKey), d.rotatingX);
    s->setValue(QLatin1String(linkedViewportModelXformsKey), d.linkedViewportModelXforms);
    s->endGroup();
}

void BehaviorSettings::load(const QString &category, const QSettings *s)
{
    // Assign defaults.
    d = BehaviorSettingsData();

    QString group = QLatin1String(groupPostfix);
    if (!category.isEmpty())
        group.insert(0, category);
    group += QLatin1Char('/');

    d.zoomSpeed = s->value(group + QLatin1String(zoomSpeedKey), d.zoomSpeed).toDouble();
    d.panningZ = s->value(group + QLatin1String(panningZKey), d.panningZ).toBool();
    d.scrollWheelPanningZ = s->value(group + QLatin1String(scrollWheelPanningZKey), d.scrollWheelPanningZ).toBool();
    d.scrollWheelZooming = s->value(group + QLatin1String(scrollWheelZoomingKey), d.scrollWheelZooming).toBool();
    d.scalingY = s->value(group + QLatin1String(scalingYKey), d.scalingY).toInt();
    d.rotatingX = s->value(group + QLatin1String(rotatingXKey), d.rotatingX).toBool();
    d.linkedViewportModelXforms = s->value(group + QLatin1String(linkedViewportModelXformsKey), d.linkedViewportModelXforms).toBool();
}

bool BehaviorSettings::equals(const BehaviorSettings &bs) const
{
    return d.zoomSpeed == bs.d.zoomSpeed
        && d.panningZ == bs.d.panningZ
        && d.scrollWheelPanningZ == bs.d.scrollWheelPanningZ
        && d.scrollWheelZooming == bs.d.scrollWheelZooming
        && d.scalingY == bs.d.scalingY
        && d.rotatingX == bs.d.rotatingX
        && d.linkedViewportModelXforms == bs.d.linkedViewportModelXforms
        ;
}
