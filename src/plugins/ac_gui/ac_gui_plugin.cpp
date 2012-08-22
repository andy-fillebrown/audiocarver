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

#include "ac_gui_plugin.h"
#include <icore.h>
//#include <ac_gui_database.h>
#include <ac_gui_session_editor.h>
//#include <ac_gui_mainwidget.h>
//#include <ac_gui_mainwindowextension.h>
//#include <ac_selecteditemspropertyview.h>
//#include <ac_trackview.h>
#include <mainwindow.h>
#include <QtPlugin>

//#ifdef QT_DEBUG
//static bool test();
//#endif

namespace Ac {
namespace Gui {

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
//    (new Database())->init();
    (new Editor)->init();
//    addAutoReleasedObject(new MainWindowExtension);
    return true;
}

void Plugin::extensionsInitialized()
{
//    ::Core::MainWindow *mw = ::Core::ICore::instance()->mainWindow();
//    MainWidget *widget = new MainWidget(mw);
//    mw->setCentralWidget(widget);
//#ifdef QT_DEBUG
//    test();
//#endif
}

}
}

Q_EXPORT_PLUGIN(Ac::Gui::Plugin)

//#ifdef QT_DEBUG

//#include <ac_ientity.h>
//#include <mi_idataobjectfactory.h>
//#include <mi_imodeldata.h>
//#include <mi_imodelitem.h>

//#define RUN(x) if (!x()) return false
//#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

//using namespace Ac;

//bool test_1()
//{
//    // Make sure querying super-aggregators succeeds.
//    // Super-aggregators should create aggregates on demand.
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    IEntity *entity = query<IEntity>(control_curve);
//    CHECK(entity);
//    return true;
//}

//bool test_2()
//{
//    // Make sure querying constant super-aggregators fails.
//    // Constant super-aggregators should not create aggregates on demand.
//    const IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    const IEntity *entity = query<IEntity>(control_curve);
//    CHECK(!entity);
//    return true;
//}

//bool test_3()
//{
//    // Make sure querying aggregates for other aggregates succeeds.
//    // Aggregates should pass the query to their aggregator.
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    IModelData *data = query<IModelData>(control_curve);
//    CHECK(data);
//    IEntity *entity = query<IEntity>(data);
//    CHECK(entity);
//    return true;
//}

//bool test_4()
//{
//    // Make sure querying constant aggregates for other aggregates does not create aggregates on demand.
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    const IModelData *data = query<IModelData>(control_curve);
//    CHECK(data);
//    const IEntity *entity = query<IEntity>(data);
//    CHECK(!entity);
//    return true;
//}

//bool test_5()
//{
//    // Make sure querying constant aggregates succeeds for an aggregate that was previously created on demand.
//    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(ControlCurveItem);
//    CHECK(control_curve);
//    IEntity *entity = query<IEntity>(control_curve);
//    CHECK(entity);
//    const IAggregator *const_control_curve = control_curve;
//    const IEntity *const_entity = query<IEntity>(const_control_curve);
//    CHECK(const_entity);
//    return true;
//}

//bool test_create_item(IDataObjectFactory *factory, int itemType)
//{
//    IAggregator *item = factory->create(itemType);
//    if (!item)
//        return false;
//    delete item;
//    return true;
//}

//bool test_6()
//{
//    // Make sure all item types can be created.
//    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
//    // Don't create a score item since it makes Score::instance() return an
//    // unused score.
//    CHECK(test_create_item(factory, TrackItem));
//    CHECK(test_create_item(factory, TrackListItem));
//    CHECK(test_create_item(factory, NoteItem));
//    CHECK(test_create_item(factory, NoteListItem));
//    CHECK(test_create_item(factory, PitchCurveItem));
//    CHECK(test_create_item(factory, ControlCurveItem));
//    CHECK(test_create_item(factory, ControlCurveListItem));
//    CHECK(test_create_item(factory, GridSettingsItem));
//    CHECK(test_create_item(factory, TimeGridLineItem));
//    CHECK(test_create_item(factory, TimeGridLineListItem));
//    CHECK(test_create_item(factory, PitchGridLineItem));
//    CHECK(test_create_item(factory, PitchGridLineListItem));
//    CHECK(test_create_item(factory, ControlGridLineItem));
//    CHECK(test_create_item(factory, ControlGridLineListItem));
//    CHECK(test_create_item(factory, ViewSettingsItem));
//    CHECK(test_create_item(factory, ProjectSettingsItem));
//    return true;
//}

//bool test()
//{
//    RUN(test_6);
//    RUN(test_5);
//    RUN(test_4);
//    RUN(test_3);
//    RUN(test_2);
//    RUN(test_1);
//    qDebug() << "Ac::GuiPlugin tests passed.";
//    return true;
//}

//#endif // #ifdef QT_DEBUG
