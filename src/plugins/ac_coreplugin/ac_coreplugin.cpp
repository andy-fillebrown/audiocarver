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

#include "ac_coreplugin.h"

//#include <ac_database.h>
//#include <ac_factory.h>
//#include <ac_model.h>

#include <ac_namespace.h>

#include <pluginmanager.h>

#include <QtPlugin>

bool AcCorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    Mi::appendItemType(Ac::ScoreItem, "Score");
    Mi::appendItemType(Ac::TrackItem, "Track");
    Mi::appendItemType(Ac::NoteItem, "Note");
    Mi::appendItemType(Ac::PitchCurveItem, "PitchCurve");
    Mi::appendItemType(Ac::ControlCurveItem, "ControlCurve");
    Mi::appendItemType(Ac::GridSettingsItem, "GridSettings");
    Mi::appendItemType(Ac::TimeGridLineItem, "TimeGridLine");
    Mi::appendItemType(Ac::PitchGridLineItem, "PitchGridLine");
    Mi::appendItemType(Ac::ControlGridLineItem, "ControlGridLine");
    Mi::appendItemType(Ac::ViewSettingsItem, "ViewSettings");
    Mi::appendItemType(Ac::ProjectSettingsItem, "ProjectSettings");

    Mi::appendItemDataRole(Ac::PointsRole, "points");
    Mi::appendItemDataRole(Ac::ControlIdRole, "controlId");
    Mi::appendItemDataRole(Ac::LocationRole, "location");
    Mi::appendItemDataRole(Ac::LabelRole, "label");
    Mi::appendItemDataRole(Ac::PriorityRole, "priority");
    Mi::appendItemDataRole(Ac::InstrumentRole, "instrument");
    Mi::appendItemDataRole(Ac::LengthRole, "length");
    Mi::appendItemDataRole(Ac::VolumeRole, "volume");
    Mi::appendItemDataRole(Ac::ColorRole, "color");
    Mi::appendItemDataRole(Ac::VisibilityRole, "visible");
    Mi::appendItemDataRole(Ac::RecordingRole, "recording");
    Mi::appendItemDataRole(Ac::TimePositionRole, "timePosition");
    Mi::appendItemDataRole(Ac::PitchPositionRole, "pitchPosition");
    Mi::appendItemDataRole(Ac::ControlPositionRole, "controlPosition");
    Mi::appendItemDataRole(Ac::TimeScaleRole, "timeScale");
    Mi::appendItemDataRole(Ac::PitchScaleRole, "pitchScale");
    Mi::appendItemDataRole(Ac::ControlScaleRole, "controlScale");
    Mi::appendItemDataRole(Ac::OutputDirectoryRole, "outputDirectory");
    Mi::appendItemDataRole(Ac::InstrumentDirectoryRole, "instrumentDirectory");
    Mi::appendItemDataRole(Ac::AudioFileTypeRole, "audioFileType");
    Mi::appendItemDataRole(Ac::SampleRateRole, "sampleRate");
    Mi::appendItemDataRole(Ac::ControlRateRole, "controlRate");
    Mi::appendItemDataRole(Ac::CurveRateRole, "curveRate");
    Mi::appendItemDataRole(Ac::StartTimeRole, "startTime");
    Mi::appendItemDataRole(Ac::SnapEnabledRole, "snapEnabled");
    Mi::appendItemDataRole(Ac::GridSnapEnabledRole, "gridSnapEnabled");
    Mi::appendItemDataRole(Ac::TimeSnapRole, "timeSnap");
    Mi::appendItemDataRole(Ac::PitchSnapRole, "pitchSnap");
    Mi::appendItemDataRole(Ac::ControlSnapRole, "controlSnap");

//    addAutoReleasedObject(new ObjectFactory);
//    addAutoReleasedObject(new FilerFactory);
//    addAutoReleasedObject(new Database);
//    addAutoReleasedObject(new Model);

    return true;
}

Q_EXPORT_PLUGIN(AcCorePlugin)
