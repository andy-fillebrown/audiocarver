/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_core_plugin.h"
#include "ac_core_database.h"
#include "ac_core_databaseobjectfactory.h"
#include "ac_core_filerfactory.h"
#include "ac_core_model.h"
#include "ac_core_namespace.h"
#include <isession.h>
#include <pluginmanager.h>
#include <QtPlugin>

namespace Ac {
namespace Core {

Plugin::Plugin()
{
    new DatabaseObjectFactory;
    new Database;
    new FilerFactory;
    new Model;
}

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    appendItemType(ScoreItem, "Score");
    appendItemType(TrackItem, "Track");
    appendItemType(TrackListItem, "TrackList");
    appendItemType(NoteItem, "Note");
    appendItemType(NoteListItem, "NoteList");
    appendItemType(PitchCurveItem, "PitchCurve");
    appendItemType(ControlCurveItem, "ControlCurve");
    appendItemType(GridSettingsItem, "GridSettings");
    appendItemType(TimeGridLineItem, "TimeGridLine");
    appendItemType(TimeGridLineListItem, "TimeGridLineList");
    appendItemType(PitchGridLineItem, "PitchGridLine");
    appendItemType(PitchGridLineListItem, "PitchGridLineList");
    appendItemType(ControlGridLineItem, "ControlGridLine");
    appendItemType(ControlGridLineListItem, "ControlGridLineList");
    appendItemType(GridSettingsItem, "GridSettings");
    appendItemType(ProjectSettingsItem, "ProjectSettings");
    appendItemType(ViewSettingsItem, "ViewSettings");
    appendItemDataRole(PointsRole, "points");
    appendItemDataRole(ControlTypeRole, "controlType");
    appendItemDataRole(LocationRole, "location");
    appendItemDataRole(LabelRole, "label");
    appendItemDataRole(PriorityRole, "priority");
    appendItemDataRole(InstrumentRole, "instrument");
    appendItemDataRole(LengthRole, "length");
    appendItemDataRole(VolumeRole, "volume");
    appendItemDataRole(ColorRole, "color");
    appendItemDataRole(VisibilityRole, "visible");
    appendItemDataRole(TimePositionRole, "timePosition");
    appendItemDataRole(PitchPositionRole, "pitchPosition");
    appendItemDataRole(ControlPositionRole, "controlPosition");
    appendItemDataRole(TimeScaleRole, "timeScale");
    appendItemDataRole(PitchScaleRole, "pitchScale");
    appendItemDataRole(ControlScaleRole, "controlScale");
    appendItemDataRole(OutputDirectoryRole, "outputDirectory");
    appendItemDataRole(InstrumentDirectoryRole, "instrumentDirectory");
    appendItemDataRole(AudioFileTypeRole, "audioFileType");
    appendItemDataRole(SampleRateRole, "sampleRate");
    appendItemDataRole(ControlRateRole, "controlRate");
    appendItemDataRole(CurveRateRole, "curveRate");
    appendItemDataRole(StartTimeRole, "startTime");
    appendItemDataRole(SnapEnabledRole, "snapEnabled");
    appendItemDataRole(GridSnapEnabledRole, "gridSnapEnabled");
    appendItemDataRole(TimeSnapRole, "timeSnap");
    appendItemDataRole(PitchSnapRole, "pitchSnap");
    appendItemDataRole(ControlSnapRole, "controlSnap");
    return true;
}

}
}

Q_EXPORT_PLUGIN(Ac::Core::Plugin)
