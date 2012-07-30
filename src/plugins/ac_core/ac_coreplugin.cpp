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

#include <ac_core_namespace.h>
//#include <ac_core_database.h>

#include <pluginmanager.h>

#include <QtPlugin>

#ifdef QT_DEBUG
static bool test();
#endif

using namespace Mi;

namespace Ac {

//using namespace Core;

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

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

//    (new Database)->init();

    return true;
}

void CorePlugin::extensionsInitialized()
{
#ifdef QT_DEBUG
    test();
#endif
}

} // namespace Ac

Q_EXPORT_PLUGIN(Ac::CorePlugin)

//#ifdef QT_DEBUG

//#include <mi_iclassfactory.h>
//#include <mi_imodeldata.h>
//#include <mi_imodelitem.h>

//#define RUN(x) if (!x()) return false
//#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

//using namespace Ac;

//bool test_1()
//{
//    // Make sure querying aggregators succeeds.
//    // Aggregators should create aggregates on demand.
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    IModelItem *item = query<IModelItem>(control_curve);
//    CHECK(item);
//    return true;
//}

//bool test_2()
//{
//    // Make sure querying constant aggregators fails.
//    // Constant aggregators should not create aggregates on demand.
//    const IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    const IModelItem *item = query<IModelItem>(control_curve);
//    CHECK(!item);
//    return true;
//}

//bool test_3()
//{
//    // Make sure IModelData::item() succeeds.
//    // DataObject::ModelData::_item should be set in DataObject::ModelData::init().
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    IModelData *data = query<IModelData>(control_curve);
//    CHECK(data);
//    IModelItem *item = data->item();
//    CHECK(item);
//    return true;
//}

//bool test_4()
//{
//    // Make sure setting item name succeeds.
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    IModelData *data = query<IModelData>(control_curve);
//    CHECK(data);
//    CHECK(data->set("ControlCurve", NameRole));
//    CHECK("ControlCurve" == data->get<QString>(NameRole));
//    return true;
//}

//bool test()
//{
//    RUN(test_4);
//    RUN(test_3);
//    RUN(test_2);
//    RUN(test_1);
//    qDebug() << "Ac::CorePlugin tests passed.";
//    return true;
//}

//#endif // #ifdef QT_DEBUG
