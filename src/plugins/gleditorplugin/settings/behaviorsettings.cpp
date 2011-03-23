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

static const char * const zoomSpeedKey = "ZoomSpeedKey";
static const char * const panningZKey = "PanningZKey";
static const char * const scrollWheelPanningZKey = "ScrollWheelPanningZKey";
static const char * const scrollWheelZoomingKey = "ScrollWheelZoomingKey";
static const char * const scalingYKey = "ScalingYKey";
static const char * const rotatingXKey = "RotatingXKey";
static const char * const linkedViewportModelXformsKey = "LinkedViewportModelXformsKey";

static const char * const groupPostfix = "BehaviorSettings";

using namespace GLEditor;

BehaviorSettings::BehaviorSettings()
    :   m_zoomSpeed(1.0f)
    ,   m_panningZ(true)
    ,   m_scrollWheelPanningZ(true)
    ,   m_scrollWheelZooming(true)
    ,   m_scalingY(false)
    ,   m_rotatingX(true)
    ,   m_linkedViewportModelXforms(true)
{
}

void BehaviorSettings::toSettings(const QString &category, QSettings *s) const
{
    QString group = QLatin1String(groupPostfix);
    if (!category.isEmpty())
        group.insert(0, category);

    s->beginGroup(group);
    s->setValue(QLatin1String(zoomSpeedKey), m_zoomSpeed);
    s->setValue(QLatin1String(panningZKey), m_panningZ);
    s->setValue(QLatin1String(scrollWheelPanningZKey), m_scrollWheelPanningZ);
    s->setValue(QLatin1String(scrollWheelZoomingKey), m_scrollWheelZooming);
    s->setValue(QLatin1String(scalingYKey), m_scalingY);
    s->setValue(QLatin1String(rotatingXKey), m_rotatingX);
    s->setValue(QLatin1String(linkedViewportModelXformsKey), m_linkedViewportModelXforms);
    s->endGroup();
}

void BehaviorSettings::fromSettings(const QString &category, const QSettings *s)
{
    // Assign defaults.
    *this = BehaviorSettings();

    QString group = QLatin1String(groupPostfix);
    if (!category.isEmpty())
        group.insert(0, category);
    group += QLatin1Char('/');

    m_zoomSpeed = s->value(group + QLatin1String(zoomSpeedKey), m_zoomSpeed).toDouble();
    m_panningZ = s->value(group + QLatin1String(panningZKey), m_panningZ).toBool();
    m_scrollWheelPanningZ = s->value(group + QLatin1String(scrollWheelPanningZKey), m_scrollWheelPanningZ).toBool();
    m_scrollWheelZooming = s->value(group + QLatin1String(scrollWheelZoomingKey), m_scrollWheelZooming).toBool();
    m_scalingY = s->value(group + QLatin1String(scalingYKey), m_scalingY).toInt();
    m_rotatingX = s->value(group + QLatin1String(rotatingXKey), m_rotatingX).toBool();
    m_linkedViewportModelXforms = s->value(group + QLatin1String(linkedViewportModelXformsKey), m_linkedViewportModelXforms).toBool();
}

bool BehaviorSettings::equals(const BehaviorSettings &bs) const
{
    return m_zoomSpeed == bs.m_zoomSpeed
        && m_panningZ == bs.m_panningZ
        && m_scrollWheelPanningZ == bs.m_scrollWheelPanningZ
        && m_scrollWheelZooming == bs.m_scrollWheelZooming
        && m_scalingY == bs.m_scalingY
        && m_rotatingX == bs.m_rotatingX
        && m_linkedViewportModelXforms == bs.m_linkedViewportModelXforms
        ;
}
