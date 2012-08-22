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

#include "ac_core_plugin.h"
#include "ac_core_namespace.h"
#include "ac_core_database.h"
#include "ac_core_databaseobjectfactory.h"
#include "ac_core_filerfactory.h"
#include <pluginmanager.h>
#include <QtPlugin>

#ifdef QT_DEBUG
static bool test();
#endif

using namespace Mi;

namespace Ac {
namespace Core {

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    appendItemType(ScoreItem, "Score");
    appendItemType(TrackItem, "Track");
    appendItemType(NoteItem, "Note");
    appendItemType(PitchCurveItem, "PitchCurve");
    appendItemType(ControlCurveItem, "ControlCurve");
    appendItemType(GridSettingsItem, "GridSettings");
    appendItemType(TimeGridLineItem, "TimeGridLine");
    appendItemType(PitchGridLineItem, "PitchGridLine");
    appendItemType(ControlGridLineItem, "ControlGridLine");
    appendItemType(ViewSettingsItem, "ViewSettings");
    appendItemType(ProjectSettingsItem, "ProjectSettings");
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
    appendItemDataRole(RecordingRole, "recording");
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
    (new Session::DatabaseObjectFactory)->initialize();
    (new Session::Database)->initialize();
    (new Session::FilerFactory)->initialize();
    return true;
}

void Plugin::extensionsInitialized()
{
#ifdef QT_DEBUG
    test();
#endif
}

}
}

Q_EXPORT_PLUGIN(Ac::Core::Plugin)

#ifdef QT_DEBUG

#include <mi_iaggregate.h>
#include <mi_idatabaseobjectfactory.h>
#include <mi_imodeldata.h>
#include <mi_imodelitem.h>
#include <QtDebug>

#define RUN(x) if (!x()) return false
#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

using namespace Ac;

bool test_1()
{
    // Make sure querying aggregates succeeds.
    IAggregate *control_curve = IDatabaseObjectFactory::instance()->create(ControlCurveItem);
    CHECK(control_curve);
    IModelItem *item = query<IModelItem>(control_curve);
    CHECK(item);
    delete control_curve;
    return true;
}

bool test_2()
{
    // Make sure setting item name succeeds.
    IAggregate *control_curve = IDatabaseObjectFactory::instance()->create(ControlCurveItem);
    CHECK(control_curve);
    IModelData *data = query<IModelData>(control_curve);
    CHECK(data);
    CHECK(data->set("ControlCurve", NameRole));
    CHECK("ControlCurve" == data->get<QString>(NameRole));
    delete control_curve;
    return true;
}

bool test()
{
    RUN(test_2);
    RUN(test_1);
    qDebug() << "Ac::Core::Plugin tests passed.";
    return true;
}

#endif
