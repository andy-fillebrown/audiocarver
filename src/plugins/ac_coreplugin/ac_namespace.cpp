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

#include <ac_namespace.h>

static const QMap<int, QString> &itemDataRoleMap()
{
    static QMap<int, QString> map;
    if (map.isEmpty()) {
        map.insert(Ac::PointsRole, "points");
        map.insert(Ac::ControlIdRole, "controlId");
        map.insert(Ac::LocationRole, "location");
        map.insert(Ac::LabelRole, "label");
        map.insert(Ac::PriorityRole, "priority");
        map.insert(Ac::InstrumentRole, "instrument");
        map.insert(Ac::LengthRole, "length");
        map.insert(Ac::VolumeRole, "volume");
        map.insert(Ac::ColorRole, "color");
        map.insert(Ac::VisibilityRole, "visible");
        map.insert(Ac::RecordingRole, "recording");
        map.insert(Ac::TimePositionRole, "timePosition");
        map.insert(Ac::PitchPositionRole, "pitchPosition");
        map.insert(Ac::ControlPositionRole, "controlPosition");
        map.insert(Ac::TimeScaleRole, "timeScale");
        map.insert(Ac::PitchScaleRole, "pitchScale");
        map.insert(Ac::ControlScaleRole, "controlScale");
        map.insert(Ac::OutputDirectoryRole, "outputDirectory");
        map.insert(Ac::InstrumentDirectoryRole, "instrumentDirectory");
        map.insert(Ac::AudioFileTypeRole, "audioFileType");
        map.insert(Ac::SampleRateRole, "sampleRate");
        map.insert(Ac::ControlRateRole, "controlRate");
        map.insert(Ac::CurveRateRole, "curveRate");
    }
    return map;
}

static const QMap<int, QString> &itemTypeMap()
{
    static QMap<int, QString> map;
    if (map.isEmpty()) {
        map.insert(Ac::ScoreItem, "Score");
        map.insert(Ac::TrackItem, "Track");
        map.insert(Ac::NoteItem, "Note");
        map.insert(Ac::PitchCurveItem, "PitchCurve");
        map.insert(Ac::ControlCurveItem, "ControlCurve");
        map.insert(Ac::GridSettingsItem, "GridSettings");
        map.insert(Ac::TimeGridLineItem, "TimeGridLine");
        map.insert(Ac::PitchGridLineItem, "PitchGridLine");
        map.insert(Ac::ControlGridLineItem, "ControlGridLine");
        map.insert(Ac::ViewSettingsItem, "ViewSettings");
        map.insert(Ac::ProjectSettingsItem, "ProjectSettings");
    }
    return map;
}

namespace Ac {

QString itemDataRoleString(int itemDataRole)
{
    const QMap<int, QString> &map = itemDataRoleMap();
    if (map.contains(itemDataRole))
        return map.value(itemDataRole);
    return Mi::itemDataRoleString(itemDataRole);
}

int itemDataRole(const QString &itemDataRoleString)
{
    const QMap<int, QString> &map = itemDataRoleMap();
    QList<QString> values = map.values();
    if (values.contains(itemDataRoleString))
        return map.keys().at(values.indexOf(itemDataRoleString));
    return Mi::itemDataRole(itemDataRoleString);
}

QString itemTypeString(int itemType)
{
    const QMap<int, QString> &map = itemTypeMap();
    if (map.contains(itemType))
        return map.value(itemType);
    return QString();
}

int itemType(const QString &itemTypeString)
{
    const QMap<int, QString> &map = itemTypeMap();
    QList<QString> values = map.values();
    if (values.contains(itemTypeString))
        return map.keys().at(values.indexOf(itemTypeString));
    return -1;
}

} // namespace Ac
